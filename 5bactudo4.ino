#include <Servo.h>

// Khởi tạo các đối tượng servo
Servo servoDe;
Servo servoVai;
Servo servoKhuyu;
Servo servoCoTay;
Servo servoGap;

// Định nghĩa chân tín hiệu
const int pinDe = 4;
const int pinVai = 6;
const int pinKhuyu = 5;
const int pinCoTay = 8;  
const int pinGap = 9;   

void setup() {
  // Kết nối các servo với chân tín hiệu
  servoDe.attach(pinDe);
  servoVai.attach(pinVai);
  servoKhuyu.attach(pinKhuyu);
  servoCoTay.attach(pinCoTay);
  servoGap.attach(pinGap);

  // Đưa robot về vị trí bắt đầu ban đầu khi vừa bật nguồn
  servoDe.write(160);
  servoVai.write(110);
  servoKhuyu.write(80);
  servoCoTay.write(150);
  servoGap.write(160);
  
  delay(3000); // Đợi 3 giây để chuẩn bị chạy chu trình
}

void loop() {
  // GIAI ĐOẠN 1: HÀNH TRÌNH ĐI ĐẾN VÀ GẮP VẬT (Tại góc Đế 60)

  // Bước 1: Servo Đế xoay từ 160 đến 60 độ
  for (int pos = 160; pos >= 60; pos--) {
    servoDe.write(pos);
    delay(15); 
  }
  delay(500); 

  // Bước 2: Servo Vai và Khuỷu HOẠT ĐỘNG ĐỒNG THỜI (Vươn xuống gắp)
  // Vai: 110 -> 60 | Khuỷu: 80 -> 10
  for (int step = 0; step <= 100; step++) {
    int gocVai = map(step, 0, 100, 110, 60);
    int gocKhuyu = map(step, 0, 100, 80, 10);
    servoVai.write(gocVai);
    servoKhuyu.write(gocKhuyu);
    delay(20); 
  }
  delay(500);

  // Bước 3: Servo Cổ tay hạ xuống (150 -> 90 độ)
  for (int pos = 150; pos >= 90; pos--) {
    servoCoTay.write(pos);
    delay(15);
  }
  delay(500);

  // Bước 4: Servo Gắp đóng lại từ 160 đến 50 độ (Kẹp giữ vật)
  for (int pos = 160; pos >= 50; pos--) {
    servoGap.write(pos);
    delay(15);
  }
  delay(1000); // Đợi 1 giây để kẹp chắc vật

  // GIAI ĐOẠN 2: XOAY VỀ, VƯƠN RA VÀ THẢ VẬT (Tại góc Đế 160)

  // Bước 5: Co vai và khuỷu lại đồng thời để nhấc vật lên cao
  // Vai: 60 -> 110 | Khuỷu: 10 -> 80
  for (int step = 0; step <= 100; step++) {
    int gocVai = map(step, 0, 100, 60, 110);
    int gocKhuyu = map(step, 0, 100, 10, 80);
    servoVai.write(gocVai);
    servoKhuyu.write(gocKhuyu);
    delay(20); 
  }
  delay(500);

    // Bước 6: Servo Cổ tay ngửa lên lại (90 -> 150 độ)
  for (int pos = 90; pos <= 150; pos++) {
    servoCoTay.write(pos);
    delay(15);
  }
  delay(500);

  // Bước 7: Servo Đế xoay ngược từ 60 về 160 độ (Xoay về vị trí trả vật)
  for (int pos = 60; pos <= 160; pos++) {
    servoDe.write(pos);
    delay(15); 
  }
  delay(500); 

  // Bước 8: VƯƠN VAI VÀ KHUỶU RA ĐỒNG THỜI TẠI VỊ TRÍ THẢ
  // Vai: 110 -> 60 | Khuỷu: 80 -> 10
  for (int step = 0; step <= 100; step++) {
    int gocVai = map(step, 0, 100, 110, 60);
    int gocKhuyu = map(step, 0, 100, 80, 10);
    servoVai.write(gocVai);
    servoKhuyu.write(gocKhuyu);
    delay(20); 
  }
  delay(500);

    // Bước 9: Servo Cổ tay hạ xuống góc thả (90 -> 150 độ)
  for (int pos = 90; pos >= 150; pos--) {
    servoCoTay.write(pos);
    delay(15);
  }
  delay(500);

  // Bước 10: Servo Gắp mở ra từ 50 đến 160 độ (Thả vật)
  for (int pos = 50; pos <= 160; pos++) {
    servoGap.write(pos);
    delay(15);
  }
  delay(1000); // Đợi 1 giây để vật rơi hoàn toàn

  // Bước 11: THU TAY VỀ TRẠNG THÁI BAN ĐẦU ĐỂ RESET CHU TRÌNH
  // Sau khi thả vật xong, thu tay về góc cao để khi vòng lặp lặp lại, robot sẽ xoay đế đi gắp tiếp
  // Vai: 60 -> 110 | Khuỷu: 10 -> 80
  for (int step = 0; step <= 100; step++) {
    int gocVai = map(step, 0, 100, 60, 110);
    int gocKhuyu = map(step, 0, 100, 10, 80);
    servoVai.write(gocVai);
    servoKhuyu.write(gocKhuyu);
    delay(20); 
  }

  delay(3000); // Đợi 3 giây nghỉ trước khi tự động chạy chu trình tiếp theo
}