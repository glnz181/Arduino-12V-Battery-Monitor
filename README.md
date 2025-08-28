# 12V Akü Batarya Durumu Monitörü (Arduino)

Bu proje, Arduino kullanarak 12V akünün voltajını ölçen ve batarya durumunu seri monitörde gösteren basit bir batarya izleme sistemidir. **Voltage divider** yöntemi kullanılarak Arduino'nun analog girişine bağlanan akü voltajı güvenli bir şekilde okunur.

---

## Özellikler

- 12V akü voltaj ölçümü
- Analog giriş üzerinden gerilim ölçümü (A0 pini)
- 10-bit ADC ile hassas okuma
- 10 ölçüm ortalaması ile daha stabil değerler
- Batarya yüzdesi ve durumunu hesaplama
- Seri monitörde detaylı batarya durumu göstergesi
- Voltaj seviyesine göre uyarılar ve renkli mesajlar

---

## Donanım Gereksinimleri

- Arduino Uno veya uyumlu kart
- 12V akü
- Dirençler: 20kΩ (R1) ve 10kΩ (R2)
- Bağlantı kabloları
- Seri monitör için USB bağlantısı

---

## Devre Bağlantısı

