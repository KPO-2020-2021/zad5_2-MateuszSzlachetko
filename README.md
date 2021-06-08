# Projekt 5 - Dron

## Budowanie programu i testów

W celu zbudowania programu należy użyć poniższych komend

```bash
    git submodule update --init --recursive
		cd build && cmake ..
    make
```

Następnie z poziomu build można uruchomić program

```bash
    ./Drone_run
```

i wywołać testy przechodząc do folderu test

```bash
    cd test
    ./Drone_tst
```

Przy wywołaniu make,dokumentacja doxygen utworzy się automatycznie w folderze "doc_doxygen".
W celu obejrzenia jej należy przejść do folderu i otworzyć plik index w przeglądarce.

W razie problemów proszę o kontakt <259370@student.pwr.edu.pl>

## Rozszerzenia

Możliwość wyboru dowolnego z dostępnych kolorów dla wybranego drona.