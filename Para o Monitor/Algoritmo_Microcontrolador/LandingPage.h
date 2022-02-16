#ifndef LANDING_H
#define LANDING_H

#include <Arduino.h>

//html - css - javascript page

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt" dir="ltr">

<head>
  <meta charset="utf-8">
  <title></title>
  <style>
    

    * {
      margin: 0;
      padding: 0;
      border: 0;
      outline: 0;
      box-sizing: border-box;
      list-style: none;
      font-family:  sans-serif;
    }

    .top-bar {
      width: 100%;
      position: absolute;
      z-index: 10;
      display: flex;
      top: 0;
      left: 0;
    }

    .btn-top-bar {
      flex: 1 0 25%;
      cursor: pointer;
      font-size: 4rem;
      padding: 2rem;
    }

    .btn-top-bar.active {
      background: #cfcfcf;
    }


    .btn-top-bar:not(.active):hover {
      background: #dddddd;
    }


    .container {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
    }


    .content {
      display: flex;
      flex-direction: column;
      gap: 3rem;
    }

    .name-rele {
      text-align: center;
      font-size: 4rem;
    }


    .buttons-action {
      display: flex;
      gap: 6rem;
    }


    .btn-act {
      font-size: 3.5rem;
      padding: 1rem 2rem;
      min-width: 176px;
      min-height: 97px;
      cursor: pointer;
    }

    .btn-act.on.active {
      background: rgb(1, 206, 35);
    }

    .btn-act.on {
      background: rgb(0, 126, 21);
    }

    .btn-act.off.active {
      background: rgb(255, 28, 28);
    }

    .btn-act.off {
      background: rgb(156, 0, 0);
    }
  </style>

</head>

<body>

  <div class="container">

    <div class="top-bar">
      <input type="button" value="1" class="btn-top-bar active"></button>
      <input type="button" value="2" class="btn-top-bar"></button>
      <input type="button" value="3" class="btn-top-bar"></button>
      <input type="button" value="4" class="btn-top-bar"></button>

    </div>

    <div class="content">
      <p class="name-rele">RELÉ <span class="num-rele">1</span></p>
      <div class="buttons-action">
        <button class="btn-act on">ON</button>
        <button class="btn-act off">OFF</button>
      </div>
    </div>

  </div>

  <script type="text/javascript">
    const BTNS_ACT = document.querySelectorAll('.btn-act');
    const BTNS_RELE = document.querySelectorAll('.btn-top-bar');

    const RELE = {
      '1': false,
      '2': false,
      '3': false,
      '4': false,
      '5': false,
      '6': false,
      '7': false,
      '8': false,
      '9': false,
      '10': false
    }

    let currentRELE = 1;


    function sendRequest(relayId, status) {
      var ajax = new XMLHttpRequest();
      let req = "/buttons?relay" + relayId + "=1&status=" + status;
      ajax.open("GET", req, true);
      ajax.send();
    }


    function start() {
      const ACT_ACTIVE = document.querySelector('.btn-act.active');

      if (ACT_ACTIVE !== null) {
        ACT_ACTIVE.classList.remove('active');
      }

      if (RELE[currentRELE]) {
        const on = document.querySelector('.btn-act.on');
        on.classList.add('active');
      } else {
        const off = document.querySelector('.btn-act.off');
        off.classList.add('active');
      }

    }

    start();


    BTNS_RELE.forEach(el => {

      el.addEventListener('click', () => {

        const RELE_ACTIVE = document.querySelector('.btn-top-bar.active');

        if (el != RELE_ACTIVE) {

          const NUM_RELE = document.querySelector('.num-rele');

          currentRELE = el.value;

          NUM_RELE.innerHTML = currentRELE;

          RELE_ACTIVE.classList.remove('active');
          el.classList.add('active');

          //----------------------------------------------------

          start();

        }

      })

    })



    BTNS_ACT.forEach(el => {

      el.addEventListener('click', () => {

        const ACT_ACTIVE = document.querySelector('.btn-act.active');

        if (ACT_ACTIVE !== null) {
          ACT_ACTIVE.classList.remove('active');
        }
        const btnType = el.classList;

        RELE[currentRELE] = (btnType[1] === 'on') ? true : false;

        if (RELE[currentRELE]) {
          const on = document.querySelector('.btn-act.on');
          on.classList.add('active');
        } else {
          const off = document.querySelector('.btn-act.off');
          off.classList.add('active');
        }

        sendRequest(currentRELE, RELE[currentRELE]);

      })

    })


  </script>
</body>

</html>
)rawliteral";

#endif
