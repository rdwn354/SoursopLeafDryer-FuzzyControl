#include <Fuzzy.h>

// Instantiating a Fuzzy object
Fuzzy *fuzzy = new Fuzzy();

// Fuzzy input temperature error
FuzzySet *NL = new FuzzySet(-100, -15, 0);
FuzzySet *Z = new FuzzySet(-15, 0, 15);
FuzzySet *PL = new FuzzySet(0, 15, 100);

// Fuzzy input derivative error
FuzzySet *neg = new FuzzySet(-100, -0.8, 0);
FuzzySet *zer = new FuzzySet(-0.8, 0, 0.8);
FuzzySet *pos = new FuzzySet(0, 0.8, 100);

// Fuzzy output
FuzzySet *z0 = new FuzzySet(-100, 0, 0.34);
FuzzySet *S = new FuzzySet(0, 0.34, 0.67);
FuzzySet *M = new FuzzySet(0.34, 0.67, 1);
FuzzySet *L = new FuzzySet(0.67, 1, 100);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  // Fuzzy input error
  FuzzyInput *error = new FuzzyInput(1);
  error->addFuzzySet(NL);
  error->addFuzzySet(Z);
  error->addFuzzySet(PL);
  fuzzy->addFuzzyInput(error);

  // Fuzzy input derivative error
  FuzzyInput *dError = new FuzzyInput(2);
  dError->addFuzzySet(neg);
  dError->addFuzzySet(zer);
  dError->addFuzzySet(pos);
  fuzzy->addFuzzyInput(dError);  

  // Fuzzy output
  FuzzyOutput *temperature = new FuzzyOutput(1);
  temperature->addFuzzySet(z0);
  temperature->addFuzzySet(S);
  temperature->addFuzzySet(M);
  temperature->addFuzzySet(L);
  fuzzy->addFuzzyOutput(temperature);  
  
  // Fuzzy rules
  FuzzyRuleAntecedent *ifErrorisNL_and_dErrorisNeg = new FuzzyRuleAntecedent();
  ifErrorisNL_and_dErrorisNeg->joinWithAND(NL, neg);
  FuzzyRuleConsequent *thenOutput_is_Z0 = new FuzzyRuleConsequent();
  thenOutput_is_Z0->addOutput(z0);
  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifErrorisNL_and_dErrorisNeg, thenOutput_is_Z0);
  fuzzy->addFuzzyRule(fuzzyRule1);

  FuzzyRuleAntecedent *ifErrorisNL_and_dErrorisZer = new FuzzyRuleAntecedent();
  ifErrorisNL_and_dErrorisZer->joinWithAND(NL, zer);
  FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifErrorisNL_and_dErrorisZer, thenOutput_is_Z0);
  fuzzy->addFuzzyRule(fuzzyRule2);

  FuzzyRuleAntecedent *ifErrorisNL_and_dErrorisPos = new FuzzyRuleAntecedent();
  ifErrorisNL_and_dErrorisPos->joinWithAND(NL, pos);
  FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifErrorisNL_and_dErrorisPos, thenOutput_is_Z0);
  fuzzy->addFuzzyRule(fuzzyRule3);

  FuzzyRuleAntecedent *ifErrorisZ_and_dErrorisNeg = new FuzzyRuleAntecedent();
  ifErrorisZ_and_dErrorisNeg->joinWithAND(Z, neg);
  FuzzyRule *fuzzyRule4 = new FuzzyRule(4, ifErrorisZ_and_dErrorisNeg, thenOutput_is_Z0);
  fuzzy->addFuzzyRule(fuzzyRule4);

  FuzzyRuleAntecedent *ifErrorisZ_and_dErrorisZer = new FuzzyRuleAntecedent();
  ifErrorisZ_and_dErrorisZer->joinWithAND(Z, zer);
  FuzzyRule *fuzzyRule5 = new FuzzyRule(5, ifErrorisZ_and_dErrorisZer, thenOutput_is_Z0);
  fuzzy->addFuzzyRule(fuzzyRule5);

  FuzzyRuleAntecedent *ifErrorisZ_and_dErrorisPos = new FuzzyRuleAntecedent();
  ifErrorisZ_and_dErrorisPos->joinWithAND(Z, pos);
  FuzzyRuleConsequent *thenOutput_is_S = new FuzzyRuleConsequent();
  thenOutput_is_S->addOutput(S);
  FuzzyRule *fuzzyRule6 = new FuzzyRule(6, ifErrorisZ_and_dErrorisPos, thenOutput_is_S);
  fuzzy->addFuzzyRule(fuzzyRule6);

  FuzzyRuleAntecedent *ifErrorisPL_and_dErrorisNeg = new FuzzyRuleAntecedent();
  ifErrorisPL_and_dErrorisNeg->joinWithAND(PL, neg);
  FuzzyRule *fuzzyRule7 = new FuzzyRule(7, ifErrorisPL_and_dErrorisNeg, thenOutput_is_S);
  fuzzy->addFuzzyRule(fuzzyRule7);

  FuzzyRuleAntecedent *ifErrorisPL_and_dErrorisZer = new FuzzyRuleAntecedent();
  ifErrorisPL_and_dErrorisZer->joinWithAND(PL, zer);
  FuzzyRuleConsequent *thenOutput_is_M = new FuzzyRuleConsequent();
  thenOutput_is_M->addOutput(M);
  FuzzyRule *fuzzyRule8 = new FuzzyRule(8, ifErrorisPL_and_dErrorisZer, thenOutput_is_M);
  fuzzy->addFuzzyRule(fuzzyRule8);

  FuzzyRuleAntecedent *ifErrorisPL_and_dErrorisPos = new FuzzyRuleAntecedent();
  ifErrorisPL_and_dErrorisPos->joinWithAND(PL, pos);
  FuzzyRuleConsequent *thenOutput_is_L = new FuzzyRuleConsequent();
  thenOutput_is_L->addOutput(L);
  FuzzyRule *fuzzyRule9 = new FuzzyRule(9, ifErrorisPL_and_dErrorisPos, thenOutput_is_L);
  fuzzy->addFuzzyRule(fuzzyRule9);
}

void loop() {
  // get random entrances
  int input1 = random(-100, 100);
  int input2 = random(-1, 1);

  Serial.println("\n\n\nEntrance: ");
  Serial.print("\tTemperature Error: ");
  Serial.print(input1);
  Serial.print(", Derivative Error: ");
  Serial.print(input2);

  fuzzy->setInput(1, input1);
  fuzzy->setInput(2, input2);

  fuzzy->fuzzify();

  Serial.println("Input: ");
  Serial.print("\tTemperature Error: ");
  Serial.print(input1);
  Serial.print(", Derivative Error: ");
  Serial.println(input2);

  float temperature = fuzzy->defuzzify(1);

  Serial.println("Output: ");
  Serial.print("\tTemperature: ");
  Serial.println(temperature);

  // wait 12 seconds
  delay(12000);
}
