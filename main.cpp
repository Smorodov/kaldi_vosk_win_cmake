#include <iostream>
#include <iomanip>
#include <atomic>
#include <cmath>
#include <thread>
#include <audio>
#include <vosk_api.h>
#include <locale.h>
#include <audio>


using namespace std::experimental;

bool is_default_device(const audio_device& d)
{
    if (d.is_input())
    {
        auto default_in = get_default_audio_input_device();
        return default_in.has_value() && d.device_id() == default_in->device_id();
    }
    else if (d.is_output())
    {
        auto default_out = get_default_audio_output_device();
        return default_out.has_value() && d.device_id() == default_out->device_id();
    }

    return false;
}

void print_device_info(const audio_device& d)
{
    std::cout << "- \"" << d.name() << "\", ";
    std::cout << "sample rate = " << d.get_sample_rate() << " Hz, ";
    std::cout << "buffer size = " << d.get_buffer_size_frames() << " frames, ";
    std::cout << (d.is_input() ? d.get_num_input_channels() : d.get_num_output_channels()) << " channels";
    std::cout << (is_default_device(d) ? " [DEFAULT DEVICE]\n" : "\n");
};

void print_device_list(const audio_device_list& list)
{
    for (auto& item : list)
    {
        print_device_info(item);
    }
}

void print_all_devices()
{
    std::cout << "Input devices:\n==============\n";
    print_device_list(get_audio_input_device_list());

    std::cout << "\nOutput devices:\n===============\n";
    print_device_list(get_audio_output_device_list());
}

static VoskModel* model;
static VoskRecognizer* recognizer;
static int counter=0;
float buffer[32000];
int ptr = 0;

void callback(audio_device&, audio_device_io<float>& io) noexcept
{
    if (!io.input_buffer.has_value())
        return;
    
    for (int i = 0; i < io.input_buffer->size_frames(); ++i)
    {
        buffer[i+ptr]=io.input_buffer->data()[i]*32768;
    }

    if (io.input_buffer->size_frames() + ptr >= 1600)
    { 
        ptr = 0;
    }
    else
    {
        ptr += io.input_buffer->size_frames();
    }
}

// Adaptation reference
// https://alphacephei.com/vosk/adaptation

int main()
{
    float sample_rate = 8000;
    int batch_size = 640;
    setlocale(LC_ALL, "ru_RU.utf8");
    
    model = vosk_model_new("model/vosk-model-ru-0.10");
    recognizer = vosk_recognizer_new(model, sample_rate);
    

    // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1386r0.pdf
    print_all_devices();

    set_audio_device_list_callback(audio_device_list_event::device_list_changed, [] {
        std::cout << "\n=== Audio device list changed! ===\n\n";
        print_all_devices();
        });

    set_audio_device_list_callback(audio_device_list_event::default_input_device_changed, [] {
        std::cout << "\n=== Default input device changed! ===\n\n";
        print_all_devices();
        });

    set_audio_device_list_callback(audio_device_list_event::default_output_device_changed, [] {
        std::cout << "\n=== Default output device changed! ===\n\n";
        print_all_devices();
        });


    

    auto device = get_default_audio_input_device();
    if (!device)
    {
        return 1;
    }

    device->set_sample_rate(sample_rate);

    std::cout << " Sample rate " << device->get_sample_rate() << std::endl;    
    device->set_buffer_size_frames(batch_size);
    device->connect(callback);

    device->start();
    while (device->is_running())
    {
        if (ptr >= batch_size)
        {
            if (vosk_recognizer_accept_waveform_f(recognizer, (float*)buffer, (int)ptr))
            {
                printf("%s\n", vosk_recognizer_result(recognizer));
            }
            else
            {
                const char* partial = vosk_recognizer_partial_result(recognizer);
                if (partial[17] != '"')
                {
                    printf("%s\n", partial);
                }
            }
            ptr = 0;            
        }
        if (GetKeyState(27) & 0x8000)
        {
            device->stop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    vosk_recognizer_free(recognizer);
    vosk_model_free(model);
}
