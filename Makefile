OBJECTS=TransducingLayer.o Matrix.o CharacteristicMatrix.o HomogeneousCharacteristicMatrix.o LaserBeam.o CapSimulation.o HomogeneousCharacteristicMatrix.o CapMaterialInterface.o ImplantedDiamond.o ThreadedCapSimulationRunner.o TrimFileVacancyConcentrationCalculator.o DamageModelInterface.o DamageModelFactory.o
MODELS=OliveroDamageModel.o LagomarsinoDamageModel.o UndamagedDiamondModel.o PreviousDamagedDiamondModel.o IndependentExponentialModel.o
CPPFLAGS=-O3 -Wall -Winvalid-pch

.PHONY: all
all: cap-sim FitCapData PrintModelOutput

cap-sim: main.cpp $(OBJECTS) $(MODELS)
	g++ $(CPPFLAGS) $^ -o $@ -include stdafx.h

FitCapData: FitCapData.cpp $(OBJECTS) $(MODELS)
	g++ $(CPPFLAGS) -I/opt/local/include `gsl-config --libs` $^ -o $@ -include stdafx.h

PrintModelOutput: PrintModelOutput.cpp DamageModelInterface.o DamageModelFactory.o $(MODELS)
	g++ $(CPPFLAGS) $^ -o $@ -include stdafx.h

CapSimulation.o: CharacteristicMatrix.h HomogeneousCharacteristicMatrix.h DefaultCapMaterial.h LaserBeam.h TransducingLayer.h CapMaterialInterface.h Exception.h
CharacteristicMatrix.o: Matrix.h
HomogeneousCharacteristicMatrix.o: CharacteristicMatrix.h Matrix.h
ImplantedDiamond.o: CapMaterialInterface.h TrimFileVacancyConcentrationCalculator.h TransducingLayer.h
CapMaterialInterface.o: TransducingLayer.h
DamageModelFactory.o: DamageModelInterface.h $(subst .o,.h,$(MODELS))
%Model.o: DamageModelInterface.h

%.o: %.cpp %.h stdafx.h.gch
	g++ $(CPPFLAGS) -include stdafx.h -c $< -o $@

stdafx.h.gch: stdafx.h
	g++ $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@-rm *~
	@-rm *.o
	@-rm cap-sim
	@-rm stdafx.h.gch
	@cd test && make clean
	@-rm \#*\#

.PHONY: test check
test check:
	@cd test && make
	@cppcheck --enable=all -i Stephanie-ErAs -i test . > /dev/null

.PHONY: env
env:
	emacs ./*.cpp ./*.h ./Makefile ./.gitignore
