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


```
Give examples
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
