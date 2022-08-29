# l5p_ledlayout
Переключатель цвета клавиатуры Lenovo Legion 5 Pro в зависимости от раскладки для Linux.

Создан из двух проектов.
Переключатель раскладки - https://github.com/imShara/l5p-kbl
Кэтчер переключателя раскладки - немного доработанный скрипт из этой ветки - https://stackoverflow.com/questions/35569562/how-to-catch-keyboard-layout-change-event-and-get-current-new-keyboard-layout-on

# Установка:
Скачиваем проект в домашнюю папку, создаем виртуальное окружение, устанавливаем в него необходимую библиотеку из requirements.txt
```
cd ~
mkdir scripts && cd scripts
git clone https://github.com/mapolyanin/l5p_ledlayout.git
cd l5p_ledlayout/
python3 -m venv env
source ./env/bin/activate
pip install -r requirements.txt
python3 l5p_kbl.py --help
```

Добавляем возможность переключать раскладку для непривилигированного пользователя.
Для этого создаем файл: /etc/udev/rules.d/99-kblight.rules с текстом:
```
SUBSYSTEM=="usb", ATTR{idVendor}=="048d", ATTR{idProduct}=="c965", MODE="0666"
```

Перезагружаем правила:

```
sudo udevadm control --reload-rules && sudo udevadm trigger
```


Этот скрипт можно использовать как переключатель подсветки клавиатуры вместо стандартного. 
Читайте README_l5p_klb.md

При необходимости правим в файле xmappingnotify.c, отвечающий за месторасположение скрипта и требуемый цвет.
У меня русский язык подсвечивается красным, а английский - белым, вы можете сделать как вам удобнее.

```
system("~/scripts/l5p_ledlayout/venv/bin/bin/python3 ~/scripts/l5p_ledlayout/l5p_kbl.py static ff0000");

} else {

system("~/scripts/l5p_ledlayout/venv/bin/bin/python3 ~/scripts/l5p_ledlayout/l5p_kbl.py static ffffff");
```

Компилируем файл xmappingnotify.c и проверяем его работоспособность:
```
gcc -Wall -O2 xmappingnotify.c -o xmappingnotify -lX11
./xmappingnotify

```
Если все работает как надо, добавляем файл xmappingnotify в автозагрузку
