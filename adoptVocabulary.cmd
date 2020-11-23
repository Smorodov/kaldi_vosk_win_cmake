fstsymbols --save_osymbols=words.txt build/Release/model/vosk-model-small-ru-0.4/graph/Gr.fst
farcompilestrings --fst_type=compact --symbols=words.txt --keep_symbols text.txt | \
 ngramcount | ngrammake | \
 fstconvert --fst_type=ngram > Gr.new.fst
mv Gr.new.fst Gr.fst
