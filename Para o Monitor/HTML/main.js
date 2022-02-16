const BTNS_ACT  =    document.querySelectorAll('.btn-act');
const BTNS_RELE =    document.querySelectorAll('.btn-top-bar');

const RELE =    {
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


function sendRequest(relayId, status){
    var ajax = new XMLHttpRequest();
    let req = "/buttons?relay" + relayId + "=1&status=" + status;
    ajax.open("GET", req, true);
    ajax.send();
}


function start() {
    const ACT_ACTIVE = document.querySelector('.btn-act.active');
    
    if ( ACT_ACTIVE !== null ){
        ACT_ACTIVE.classList.remove('active');
    }

    if ( RELE[currentRELE] ) {
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

        if ( el != RELE_ACTIVE ) {

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

        if ( ACT_ACTIVE !== null ){
            ACT_ACTIVE.classList.remove('active');
        }
        const btnType = el.classList;

        RELE[currentRELE] = (btnType[1] === 'on')? true : false;
    
        if ( RELE[currentRELE] ) {
            const on = document.querySelector('.btn-act.on');
            on.classList.add('active');
        } else {
            const off = document.querySelector('.btn-act.off');
            off.classList.add('active');
        }

        sendRequest(currentRELE, RELE[currentRELE]);


    })

})

