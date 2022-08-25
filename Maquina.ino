void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

#define CAPACITIVO 2
#define INDUTIVO 3
#define OTICO 4
#define ESTEIRA 5
#define ATUADOR1 6
#define ATUADOR2 7
#define RESETARMAZEMMETAL 8
#define RESETARMAZEMBRANCO 9
#define RESETARMAZEMPRETO 10
#define ALARME 11
int contador_armazem_metal = 0;
int contador_armazem_branco = 0;
int contador_armazem_preto = 0;
bool detectarItem();
String definirTipoDeItem();
bool verificarDisponibilidadeDoArmazem(String tipo_item);
void transportarItemArmazem(String tipo_item);
void setup() {
pinMode(CAPACITIVO, INPUT);
pinMode(INDUTIVO, INPUT);
pinMode(OTICO, OUTPUT);
pinMode(ESTEIRA, OUTPUT);
pinMode(ATUADOR1, OUTPUT);
pinMode(ATUADOR2, OUTPUT);
pinMode(RESETARMAZEMMETAL, INPUT);
pinMode(RESETARMAZEMBRANCO, INPUT);
pinMode(RESETARMAZEMPRETO, INPUT);
digitalWrite(ESTEIRA, HIGH);
} v
oid loop() {
String tipo_item;
if (detectarItem()) {
tipo_item = definirTipoDeItem();
if (verificarDisponibilidadeDoArmazem(tipo_item)) {
transportarItemArmazem(tipo_item);
} else {
tocarAlarme(tipo_item);
}digitalWrite(ESTEIRA, HIGH);
}
} b
ool detectarItem() {
if (digitalRead(CAPACITIVO)) {
digitalWrite(ESTEIRA, LOW);
delay(500);
return true;
} else {
return false;
}
} S
tring definirTipoDeItem() {
if (digitalRead(INDUTIVO)) {
if (digitalRead(OTICO)) {
return "metal";
}
} i
f (digitalRead(!INDUTIVO)) {
if (digitalRead(OTICO)) {
return "branco";
}
} i
f (digitalRead(!INDUTIVO)) {
if (digitalRead(!OTICO)) {
return "preto";
}
}
} b
ool verificarDisponibilidadeDoArmazem(String tipo_item) {
if (tipo_item == "metal") {
if (contador_armazem_metal >= 5) {
return false;
} else {
++contador_armazem_metal;
return true;
}
} i
f (tipo_item == "branco") {
if (contador_armazem_branco >= 5) {
return false;
} else {
++contador_armazem_branco;
return true;
}
} i
f (tipo_item == "preto") {
if (contador_armazem_preto >= 5) {
return false;
} else {
++contador_armazem_preto;
return true;
}
}
}Com o código salvo verifique o status novamente:
#O Git Bash irá retorna um status similar ao da imagem abaixo:
void transportarItemArmazem(String tipo_item) {
if (tipo_item == "metal") {
digitalWrite(ESTEIRA, HIGH);
digitalWrite(ATUADOR1, HIGH);
digitalWrite(ATUADOR2, LOW);
} i
f (tipo_item == "branco") {
digitalWrite(ESTEIRA, HIGH);
digitalWrite(ATUADOR1, LOW);
digitalWrite(ATUADOR2, HIGH);
} i
f (tipo_item == "preto") {
digitalWrite(ESTEIRA, HIGH);
digitalWrite(ATUADOR1, LOW);
digitalWrite(ATUADOR2, LOW);
} w
hile (digitalRead(CAPACITIVO));
} v
oid tocarAlarme(String tipo_item) {
digitalWrite(ALARME, HIGH);
if (tipo_item == "metal") {
while (!digitalRead(RESETARMAZEMMETAL));
while (digitalRead(RESETARMAZEMMETAL));
contador_armazem_metal = 0;
} i
f (tipo_item == "branco") {
while (!digitalRead(RESETARMAZEMBRANCO));
while (digitalRead(RESETARMAZEMBRANCO));
contador_armazem_branco = 0;
} i
f (tipo_item == "preto") {
while (!digitalRead(RESETARMAZEMPRETO));
while (digitalRead(RESETARMAZEMPRETO));
contador_armazem_preto = 0;
} d
igitalWrite(ALARME, LOW);
}
