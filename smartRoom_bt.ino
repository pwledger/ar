#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); // 블루투스 HC-05 TX → D10, RX → D11

String receivedData = ""; // 수신 데이터 저장 변수

void setup() {
    Serial.begin(9600);  // PC 시리얼 모니터 출력용
    BT.begin(9600);      // 블루투스 모듈 통신 시작

    Serial.println("블루투스 수신 대기 중...");
}

void loop() {
    if (BT.available()) {  // 블루투스 데이터가 들어오면
        receivedData = BT.readStringUntil('\n'); // 개행 문자까지 수신
        receivedData.trim();  // 앞뒤 공백 제거
        Serial.println("수신된 데이터: " + receivedData);
        
        // 쉼표로 구분된 문자열을 숫자로 변환
        int values[5];  // 리스트 값을 저장할 배열
        int index = 0;
        char *ptr = strtok((char*)receivedData.c_str(), ","); // 첫 번째 값

        while (ptr != NULL && index < 5) {
            values[index] = atoi(ptr); // 문자열을 숫자로 변환
            ptr = strtok(NULL, ",");   // 다음 값 가져오기
            index++;
        }

        // 변환된 값 출력
        Serial.println("변환된 숫자 리스트:");
        for (int i = 0; i < index; i++) {
            Serial.println(values[i]); // 숫자 개별 출력
        }
    }
}
