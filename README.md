ЛАБОРАТОРНАЯ РАБОТА № 2
по курсу «Основы программирования на C++»
Разработка двухрежимного калькулятора с использованием средств Qt

Разработать калькулятор, способный работать в двух режимах: обычном и 
инженерном (см. рис. 1).

![image](https://user-images.githubusercontent.com/99425721/232537911-3f186295-3ea3-48af-a6fd-be6526e289bf.png)
Рис. 1. Интерфейс калькулятора: слева режим обычного калькулятора, справа – 
инженерного
Основные требования:
- Режим задавать с помощью виджета RadioButton (при первом запуске по 
умолчанию должен быть выбран обычный режим).
- После выбора режима интерфейс должен динамически перестраиваться: 
изменяться ширина окна, добавляться/исчезать кнопки и т.д.
- Текущий режим должен отображаться в заголовке окна в скобках.
- Для отображения цифр использовать виджет QPlainTextEdit или аналогичный 
с установкой моноширинного шрифта.
- Интерфейс калькулятора должен быть реализован программно, без использования 
QtDesigner.
- Для выравнивания использовать виджеты управления автоматическим 
размещением элементов.
- Приветствуется использование стилей qss.
