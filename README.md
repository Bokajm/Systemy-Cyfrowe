<!-----

Yay, no errors, warnings, or alerts!

Conversion time: 0.276 seconds.


Using this Markdown file:

1. Paste this output into your source file.
2. See the notes and action items below regarding this conversion run.
3. Check the rendered output (headings, lists, code blocks, tables) for proper
   formatting and use a linkchecker before you publish this page.

Conversion notes:

* Docs to Markdown version 1.0β33
* Sun Apr 03 2022 07:48:33 GMT-0700 (PDT)
* Source doc: Systemy cyfrowe - motion control glove
----->


**Złożone systemy cyfrowe**

Marcin Malcher, Jakub Margol



1. **Temat Projektu:**

    Tematem projektu jest stworzenie rękawicy odczytującej ruchy dłoni użytkownika i na ich podstawie sterującej ruchami kursora w komputerze.


    Rękawica ma odczytywać ruchy nadgarstka w celu kontroli kursora oraz ruchy palca umożliwiające np. zarejestrowanie kliknięcia myszy.

2. **Sprzęt:**

    Projekt ma zostać wykonany przy pomocy mikrokontrolera ATmega32U4 na module Arduino Pro Micro oraz dwóch modułach akcelerometru z żyroskopem MPU6050.

3. **Software:**

    Język C/C++


    Niskopoziomowo zostanie zrealizowana obsługa I2C korzystając z rejestrów mikrokontrolera oraz odbiór danych z czujników.

4. **Bibliografia**

	Dokumentacja ATmega32U4:


    [ATmega32U4 datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf)

	Dokumentacja MPU6050:


    [MPU6050 datasheet](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)
	
    [MPU6050 register map](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf)
