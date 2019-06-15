/* funciones.js
 * Programado por Ramiro Ríos.
 * Esto es una nota de autoría parcial!
 * - 17-feb-2019 16:00 -
 * - última modificación: madrugada del 21 de febrero de 2019 -
*/

const MAX_X_CASILLEROS = 8;
const MAX_Y_CASILLEROS = 8;


var matriz_casilleros = [MAX_X_CASILLEROS * MAX_Y_CASILLEROS]; //var matriz_casilleros [MAX_X_CASILLEROS * MAX_Y_CASILLEROS];

var ESTAN_PINTANDO = false;
var THE_CHOSEN_COLOR = '';

var colores_enum = {
  'COLOR_AZUL' : 1,
  'COLOR_ROJO' : 2,
  'COLOR_VERDE' : 3,
  'COLOR_AMARILLO' : 4,
  'COLOR_BLANCO' : 5,
  'COLOR_NEGRO' : 6,
  'COLOR_ROSA' : 7,
  'COLOR_PURPURA' : 8,
  'COLOR_LIMA' : 9,
  'COLOR_TURQUESA' : 10  //fin
}
Object.freeze(colores_enum);

function agregarCampoTablero(elemento){
  document.body.appendChild(elemento);
}

function PintarYa(){ESTAN_PINTANDO = true;}
function NoPinteMas(){ ESTAN_PINTANDO=false;}


function crearTablero(){
  var contador_casillero_x = 0; // los casilleros horizontales
  var contador_casillero_y = 0; // los verticales
  var id_casillero = '';  // inicio la variable para el identificador de cada casillero

  var tablero = document.createElement('table');
  tablero.setAttribute('id', 'tablero');
//  agregarCampoTablero(tablero);
  document.onmousedown = PintarYa;
  document.onmouseup = NoPinteMas;
  document.getElementById('tablero_div').appendChild(tablero);

  for (contador_casillero_x = 0 ; contador_casillero_x < MAX_X_CASILLEROS; contador_casillero_x++){
    var columna = document.createElement('tr');
    for (contador_casillero_y = 0; contador_casillero_y < MAX_Y_CASILLEROS; contador_casillero_y++){
      var num_casillero = (contador_casillero_x * MAX_X_CASILLEROS) + contador_casillero_y;
      id_casillero = 'casillero_'+num_casillero;
      var casillero = document.createElement('td');
      casillero.setAttribute('id', id_casillero);
      // es un casillero par o impar?
      if (( (contador_casillero_x + contador_casillero_y) % 2 ) == 0)
        casillero.setAttribute('class', 'blanco');
      else
        casillero.setAttribute('class', 'negro');
      matriz_casilleros [num_casillero] = 0;
      casillero.setAttribute('onclick', 'javascript: setLed('+num_casillero+', this.id);');
      //casillero.addEventListener('mouseover', readMouseOverForLedPainting);
      casillero.onmouseover = readMouseOverForLedPainting;
      columna.appendChild(casillero);
      //console.log(id_casillero);
    }
    document.getElementById('tablero').appendChild(columna);
  }

}


function crearColores(){
	for (var cont=0; cont < 10; cont++){
		// agrega color
		var color = document.createElement('div');
		color.setAttribute('class', 'color');
    //color.style.text.color = "#000000"
    if ( cont == 0){
		  color.setAttribute('id', 'color_azul');
      color.style.backgroundColor = '#0000CC';
    }else if (cont == 1){
      color.setAttribute('id', 'color_rojo');
      color.style.backgroundColor = '#CC0000';
    }else if (cont == 2){
      color.setAttribute('id', 'color_verde');
      color.style.backgroundColor = '#00CC00';
    }else if (cont == 3){
      color.setAttribute('id', 'color_amarillo');
      color.style.backgroundColor = '#CCCC00';
    }else if (cont == 4){
      color.setAttribute('id', 'color_blanco');
      color.style.backgroundColor = '#CCCCCC';
    }else if (cont == 5){
      color.setAttribute('id', 'color_negro');
      color.style.backgroundColor = '#000000';
      //color.style.text.color = "#EEEEEE"
    }else if (cont == 6){
      color.setAttribute('id', 'color_rosa');
      color.style.backgroundColor = '#EE44EE';
    }else if (cont == 7){
      color.setAttribute('id', 'color_purpura');
      color.style.backgroundColor = '#AA00AA';  // CORREGIR!!!
    }else if (cont == 8){
      color.setAttribute('id', 'color_lima');
      color.style.backgroundColor = '#AADD00';
    }else if (cont == 9){
      color.setAttribute('id', 'color_turquesa');
      color.style.backgroundColor = '#77CCCC';
    }
    /*color.onclick=function(){
      setLed(cont, this.id);
    }*/
    var id_color = color.getAttribute('id');
    color.setAttribute('onclick', 'javascript: setPaintColor(this);');
		document.getElementById('colores_div').appendChild(color);
    color = null;
	}
}

// crearTablero();
function setLed(led, casillero){
  var casilla = document.getElementById(casillero);
  var color = document.getElementById('color_actual');
  THE_CHOSEN_COLOR = color.style.backgroundColor;
  casilla.style.backgroundColor = THE_CHOSEN_COLOR;
  matriz_casilleros[led] = THE_CHOSEN_COLOR;
  // alert('led N' + led + ' ID=' + color);
  /*
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("info").innerHTML = this.responseText;
    }
  };
  xhttp.open("POST", "setLed?N_LED=" + led +"&COLOR="+color, true);
  xhttp.send();
  */

  //alert (color.style.backgroundColor);
  //setPaintColor(color.style.backgroundColor);
}

function readMouseOverForLedPainting(){
  if (ESTAN_PINTANDO)
    this.style.backgroundColor = THE_CHOSEN_COLOR;
}

function LlenarCasilleros(color){
  for (var cont = 0; cont < (MAX_X_CASILLEROS*MAX_Y_CASILLEROS); cont++){
    document.getElementById('casillero_'+cont).style.backgroundColor = color;
    matriz_casilleros [cont] = color;
  }
}

function setPaintColor(color_para_pintar){
  document.getElementById('color_actual').style.backgroundColor = color_para_pintar.style.backgroundColor;
  THE_CHOSEN_COLOR = color_para_pintar.style.backgroundColor;
}











// funciones de prueba. TODO: aprender y borrar!
function holamundo(){
  for (var c = 0; c < 5; c++)
   document.body.appendChild(document.createTextNode('holamundo'+c));
  //document.body.createTextNode('hola mundo lalala!').appendChild();
  salto_de_linea();
}

function llenardecuadros(){
  for (var c=0; c < 8; c++){
    document.body.appendChild(document.createTextNode('coso'+c));
  }
  salto_de_linea();
}
function salto_de_linea(){
  var nodo = document.createElement('BR');
  var nodo_texto = document.createTextNode('--JUMPER--');
  nodo.appendChild(nodo_texto);
  document.body.appendChild(nodo_texto);
  document.body.appendChild(nodo);
}
