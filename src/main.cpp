// --------------------------------- BLUETOOTH SLAVE -------------------------------------
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>

Bounce btn = Bounce();

#define botao 23
#define led 2


BluetoothSerial BT;

char sinalAnterior;
bool estadoLed = false;
bool piscando = false;

// F4:65:0B:55:4F:26

unsigned long tempoAnterior = 0;
unsigned long intervalo = 250;

void setup()
{
    Serial.begin(115200);
    Serial.setTimeout(5000);
    pinMode(led, OUTPUT);
    btn.attach( botao,  INPUT_PULLUP ); 

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

     btn.update();
     if (BT.available()){

         char sinalRecebido = BT.read();

         Serial.printf("Sinal recebido: %c\n", sinalRecebido);

         if(sinalRecebido == '1'){
             digitalWrite(led, LOW);
         } else if(sinalRecebido == '0'){
             digitalWrite(led, HIGH);
         }

    }

    if (Serial.available())
    {
        char sinalMandado = Serial.read();
        BT.println(sinalMandado);
    }
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