void drawFrame() {
  tft.drawRect(FRAME_X, FRAME_Y, FRAME_W, FRAME_H, ILI9341_BLACK);
}

void LatBtn() {
  tft.fillRect(LAT_X, LAT_Y, BUT_W, BUT_H, ILI9341_WHITE);
  drawFrame();
  tft.setCursor(LAT_X + 6, LAT_Y + (BUT_H / 2));
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println("Latte");
}

void AmeBtn() {
  tft.fillRect(AME_X, AME_Y, BUT_W, BUT_H, ILI9341_WHITE);
  drawFrame();
  tft.setCursor(AME_X + 6, AME_Y + (BUT_H / 2));
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println("Americano");
}

void TempDat() {
  tft.fillRect(TEMP_X, TEMP_Y, BUT_W, BUT_H, ILI9341_WHITE);
  drawFrame();
  tft.setCursor(TEMP_X + 6, TEMP_Y + (BUT_H / 2));
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println(t1.get_temp());
}

void USDat() {
  tft.fillRect(SENS_X, SENS_Y, BUT_W, BUT_H, ILI9341_WHITE);
  drawFrame();
  tft.setCursor(SENS_X + 6, SENS_Y + (BUT_H / 2));
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println(u1.range());
}
