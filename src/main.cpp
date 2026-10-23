// --------------------------------- BLUETOOTH SLAVE -------------------------------------
#include <Arduino.h>
#include <BluetoothSerial.h>
//#include <Bounce2.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>


BluetoothSerial BT;

//botao para led & led
//Bounce btn = Bounce();
//#define botao 23
//#define led 2

#define tipoDHT DHT22
#define pinDHT 4                            


DHT dht(pinDHT, tipoDHT);

LiquidCrystal_I2C lcd (0x27, 20, 4);

unsigned long intervalo = 3000;
unsigned long tempoAnterior = 0;
//tempo usado no ex. led
//unsigned long tempoAnteriorPisca = 0;
//unsigned long tempoPressionou = 0;

//bools usados em ex. led
//bool piscando = false;
//bool pressionado = false;
//bool estadoBotao = false;
//bool estadoLed = false;



// F4:65:0B:55:4F:26




void setup()
{
    Serial.begin(115200);
    Serial.setTimeout(5000);
    dht.begin();

    lcd.init();
    lcd.backlight();


    //led ex. led & botao
    //pinMode(led, OUTPUT);
    //btn.attach( botao,  INPUT_PULLUP );

    if (BT.begin("BtSlaveGi"))
    {
        Serial.println("Bluetooth iniciado com sucesso");
        Serial.print("Endereco bluetooth: ");
        Serial.println(BT.getBtAddressString());
    }
    else
    {
        Serial.println("Erro ao iniciar o bluetooth");
    }
}

void loop()
{
    //upd botao
    //btn.update();


    float tempC = dht.readTemperature();
    float umi = dht.readHumidity();

    unsigned long tempoAtual = millis();

    if (BT.available()) //verifica se tem info no bt e mostra na serial
    {
        String msgRecebida = BT.readStringUntil('\n');
        msgRecebida.trim();
        Serial.printf("Mensagem recebida: %s", msgRecebida);
    

        //msg recebida led
        //if (msgRecebida =="L"){
        //    piscando = false;
        //    estadoLed = true;
        //}
        //else if (msgRecebida == "D"){
        //    piscando = false;
        //    estadoLed = false;
        //} 
        //else if (msgRecebida=="P"){
        //    piscando=true;
        //}
        
        
  }

    //piscando ex. led
    //if (piscando){ 
    //    if (tempoAtual - tempoAnteriorPisca >= intervalo){
    //        estadoLed = !estadoLed;  
    //        tempoAnteriorPisca = tempoAtual;
    //    }
    //}

    //digitalWrite(led, estadoLed);


    //if (btn.fell()){
    //   tempoPressionou = tempoAtual;
    //   pressionado = !pressionado;
    //   BT.println(pressionado ? "L" : "D");
    //}
    
    //if(btn.read() == LOW && tempoAtual - tempoPressionou >= 3000){
    //    BT.println("P");
    //    Serial.println("Enviado: P");
        //pressionado = true;
    //    tempoPressionou = tempoAtual;
    //}
}

    //if (BT.available()) // Verifica se tem info no BT e mostra na Serial
    //{

        //ex. ligar e desligar/piscando
        //String msgRecebida = BT.readStringUntil('\n');
        //msgRecebida.trim();
        //Serial.printf("Mensagem recebida: %s", msgRecebida);

        //if (msgRecebida == "acende")
        //{
        //    estadoLed = true;
        //    piscando = false;
        //}
        //else if (msgRecebida == "apaga")
        //{
        //    estadoLed = false;
        //    piscando = false;
        //}
        //else if (msgRecebida == "pisca")
        //{
        //    piscando = true;
        //}
        //else
        //{
        //    Serial.println("mensagem inválida");
    //    }
    //}
//
    //if (piscando)
    //{
    //    unsigned long tempoAtual = millis();
//
    //    if (tempoAtual - tempoAnterior >= intervalo)
    //    {
    //        estadoLed = !estadoLed;
    //        tempoAnterior = tempoAtual;
    //    }



        
    //}
    //digitalWrite(led, estadoLed);

//     if (Serial.available())
//     {
//         String msgEnviar = Serial.readStringUntil('\n');
//         msgEnviar.trim();
//         BT.println(msgEnviar);
//     }
// }

// --------------------------------- BLUETOOTH MASTER -------------------------------------
// #include <Arduino.h>
// #include <BluetoothSerial.h>
//
//
////F4:65:0B:55:4F:26
// BluetoothSerial BT;
//
// uint8_t endSlave[] = {0xF4, 0x65, 0x0B, 0x55, 0x4F, 0x26};
//
// void setup(){
//     Serial.begin(115200);
//     Serial.setTimeout(5000);
//
//     if (BT.begin("BtMasterGi", true))
//     {
//         Serial.println("Bluetooth iniciado com sucesso");
//     } else{
//         Serial.println("Erro ao iniciar");
//
//     }
//
//     if (BT.connect(endSlave))
//     {
//         Serial.println("Conectado com sucesso");
//     } else {
//
//         Serial.println("Erro ao conectar");
//     }
// }
//
// void loop(){
//     if (BT.available()) //Verifica se tem info no BT e mostra na Serial
//   {
//     String msgRecebida = BT.readStringUntil('\n');
//     msgRecebida.trim();
//     Serial.printf("Mensagem recebida: %s", msgRecebida);
//   }
//
//   if (Serial.available())
//   {
//     String msgEnviar = Serial.readStringUntil('\n');
//     msgEnviar.trim();
//     BT.println(msgEnviar);
//   }
// }