GXX = g++
MAIN=main
LINKEDFILE=multimediaProgramming


$(MAIN): $(MAIN).o
	$(GXX) -o $(MAIN) $(MAIN).o $(LINKEDFILE).o

$(MAIN).o: $(MAIN).cc
	$(GXX) -c -g $(MAIN).cc $(LINKEDFILE).cc

clean :
	rm $(MAIN) $(MAIN).o $(LINKEDFILE).o
