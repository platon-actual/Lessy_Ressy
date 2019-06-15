#ifndef LEDS_EN_TOTAL
#define LEDS_EN_TOTAL 1
#endif

const int leds_totales = LEDS_EN_TOTAL;

#include <FastLED.h>

#include "matrix_functions.h"
CRGB leds_pixel[leds_totales];

enum Colores {
  COLOR_AZUL = 1,
  COLOR_ROJO,
  COLOR_VERDE,
  COLOR_AMARILLO,
  COLOR_BLANCO,
  COLOR_NEGRO,
  COLOR_ROSA,
  COLOR_PURPURA,
  COLOR_LIMA,
  COLOR_TURQUESA  //fin
};

CRGB setRgbColor(CRGB cual){
  CRGB return_color;
  switch (cual){
    case COLOR_AZUL:
      return_color.blue = 200;
      return_color.red = 0;
      return_color.green = 0;
    break;
    case COLOR_ROJO:
      return_color.red = 200;
      return_color.blue = 0;
      return_color.green = 0;
    break;
  }


  return return_color;
}

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
 <head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CUADRO LED</title>
    <meta charset='utf-8'>

    <script>
      my.namespace.colores_enum = {
        COLOR_AZUL,
        COLOR_ROJO,
        COLOR_VERDE,
        COLOR_AMARILLO,
        COLOR_BLANCO,
        COLOR_NEGRO,
        COLOR_ROSA,
        COLOR_PURPURA,
        COLOR_LIMA,
        COLOR_TURQUESA  //fin
      };
      window.onload = function() {
        const MAX_X_CASILLEROS = 8;
        const MAX_Y_CASILLEROS = 8;

        function agregarCampoTablero(elemento){
          document.body.appendChild(elemento);
        }

        var contador_casillero_x = 0; // los casilleros horizontales
        var contador_casillero_y = 0; // los verticales
        var id_casillero = '';  // inicio la variable para el identificador de cada casillero

        var tablero = document.createElement('table');
        tablero.setAttribute('id', 'tablero');
        tablero.style.border = '2px solid';
        agregarCampoTablero(tablero);

        for (contador_casillero_x = 0 ; contador_casillero_x < MAX_X_CASILLEROS; contador_casillero_x++){
          var columna = document.createElement('tr');
          for (contador_casillero_y = 0; contador_casillero_y < MAX_Y_CASILLEROS; contador_casillero_y++){
            id_casillero = 'x'+contador_casillero_x+'y'+contador_casillero_y;
            var casillero = document.createElement('td');
            casillero.setAttribute('id', id_casillero);
            casillero.style.width = '25px';
            casillero.style.height = '25px';
            casillero.style.border = '1px dotted #999999';
              // es un casillero par o impar?
            if (( (contador_casillero_x + contador_casillero_y) % 2 ) == 0){
                casillero.style.background = '#ffffff';
            }else{
                casillero.style.background = '#000000';
            }
            columna.appendChild(casillero);
              //console.log(id_casillero);
          }
          document.getElementById('tablero').appendChild(columna);
        }
      }
    </script>
  </head>
  <body>
    <center>
      <b> PIXEL PANEL: toque los cuadrados! </b>
    </center>
  </body>
</html>
)=====";
