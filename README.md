# Bialik_Rogozin
Human scale arcade machine - 800 leds(WS2812B) + 9 Bathroom Scale sensors = Fun games machine
## תיאור המערכת

המיצב כולל מסך הבנוי מ800 משולשים אשר בכל אחד מהם יש נורת לד מכותבת.
לפני המיצב יש 9 אבני חישה עם 24 לדים מכותבים בכל אחת
יהאבני חישה, נבנו לפי המדריך בקישור הבא:
[hx711](https://www.instructables.com/id/Arduino-Bathroom-Scale-With-50-Kg-Load-Cells-and-H/) 
האבנים מחוברת ל2 ארדויאנו נאנו - 6 מחבורות ל1 ועוד 3 מחוברות ל2
שני בקרי הארדואינו נאנו מתקשרים בפרוטוקול 
I2C 
לבקר הטנסי ששולט בכל המערכת, בעזרת תוסף 
[אוקטו](https://www.pjrc.com/teensy/td_libs_OctoWS2811.html) 
### Prerequisites
 סביבת העבודה היא שפת סי בבקר ארדואינו נאנו ובקר טנסי 3.2
 * [IDE arduino](https://www.arduino.cc/en/Main/Software) - ארדואינו
 * [Teensyduino](https://www.arduino.cc/en/Main/Software) - תוסף לארדואינו להתקנות על הטנסי


ספריות
 * [OctoWS2811]( https://github.com/PaulStoffregen/OctoWS2811) - ספריה שעובדת עם הלדים
 * <Wire.h> - ספריה לתקשורת - כבר מותקנת בחבילת בסיס של ארדואינו
 * [OctoWS2811]( https://github.com/bogde/HX711) - ספריה שעובדת עם החיישני משקל


### התקנה

התקינו את הארדואינו והורידו את הקוד בספרייה הזאת
הורידו את הסיפריות הנלוות ומקמו אותם בתוך התיקיה של הסיפריה בתוך ארדויאנו.
תקמפלו את הקוד ותראו שעובד

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```


## Contributing


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

