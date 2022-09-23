const int coinInt = 0;
float sinVal;
int toneVal;

void setup()
{
  // Debugging output
  Serial.begin(9600);

  Serial.println("Ready...");
  pinMode(8, OUTPUT); // Definimos el pin 8 como salida.

  pinMode (2,INPUT_PULLUP);
  
  attachInterrupt(coinInt, coinISR, RISING);  // COIN wire connected to D2;
}


// total amount of money collected;
float money = 0.0;
float moneyBeeb = 0.0;

// gets incremented by the ISR;
// gets reset when coin was recognized (after train of pulses ends);
volatile int pulses = 0;
volatile long timeLastPulse = 0;


// executed for every pulse;
void coinISR()
{
  pulses++;
  timeLastPulse = millis();
}


void loop()
{

  long timeFromLastPulse = millis() - timeLastPulse;
  if (pulses > 0 && timeFromLastPulse > 200)
  {
    // sequence of pulses stopped; determine the coin type;
    if (pulses == 1)
    {
      Serial.println("1 Peso");
      money += 1;
      moneyBeeb  += 1;
       Serial.println("Recaudo : "+(String)money);
    }
    if (pulses == 2)
    {
      Serial.println("2 Pesos");
      money += 2;
       moneyBeeb  += 2;
      Serial.println("Recaudo : "+(String)money);
    }
    else if (pulses == 5)
    {
      Serial.println("5 Pesos");
      money += 5;
       moneyBeeb  += 5;
      Serial.println("Recaudo : "+(String)money);
    }
    else if (pulses == 10)
    {
      Serial.println("10 Pesos");
      money += 10;
       moneyBeeb  += 10;
      Serial.println("Recaudo : "+(String)money);
    }
    
  
    else
    {
      Serial.print("Moneda no se reconoce: ");
      Serial.print(pulses);
      Serial.println(" pulses");
    }
      if(moneyBeeb == 2){
        int threshold = 2;
        
              //generar tono de 440Hz durante 1000 ms
      tone(8, 2940);
      delay(500);
      noTone(8);
      moneyBeeb = 0;
    }

    pulses = 0;
  }
}