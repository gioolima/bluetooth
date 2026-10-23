// --------------------------------- BLUETOOTH SLAVE -------------------------------------
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <Bounce2.h>


BluetoothSerial BT;
Bounce btn = Bounce();

#define botao 23
#define led 2



unsigned long intervalo = 3000;
unsigned long tempoAnteriorPisca = 0;
unsigned long tempoPressionou = 0;
bool piscando = false;
bool pressionado = false;
bool estadoBotao = false;
bool estadoLed = false;



// F4:65:0B:55:4F:26




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

    unsigned long tempoAtual = millis();

    if (BT.available()) //verifica se tem info no bt e mostra na serial
    {
        String msgRecebida = BT.readStringUntil('\n');
        msgRecebida.trim();
        Serial.printf("Mensagem recebida: %s", msgRecebida);
    
        if (msgRecebida =="L"){
            piscando = false;
            estadoLed = true;
        }
        else if (msgRecebida == "D"){
            piscando = false;
            estadoLed = false;
        } 
        else if (msgRecebida=="P"){
            piscando=true;
        }      
  }

    if (piscando){ 
        if (tempoAtual - tempoAnteriorPisca >= intervalo){
            estadoLed = !estadoLed;  
            tempoAnteriorPisca = tempoAtual;
        }
    }

    digitalWrite(led, estadoLed);


    if (btn.fell()){
       tempoPressionou = tempoAtual;
       pressionado = !pressionado;
       BT.println(pressionado ? "L" : "D");
    }
    
    if(btn.read() == LOW && tempoAtual - tempoPressionou >= 3000){
        BT.println("P");
        Serial.println("Enviado: P");
        //pressionado = true;
        tempoPressionou = tempoAtual;
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