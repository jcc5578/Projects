onload = function() {
    if ('speechSynthesis' in window) with (speechSynthesis) {

        console.log('started text2speech-test.js');

        var playEle = document.querySelector('#tts-button');

        var synth = speechSynthesis;
        var flag = false;
        var playing = false;

        playEle.addEventListener('click', onClickPlay);

        function onClickPlay() {
            console.log('click detected!');

            var text = 'Hello there! Welcome to our web app! Please choose a tab from the top of the page.'
            console.log(text);
            utterance = new SpeechSynthesisUtterance(text);
            
            utterance.voice = getVoices()[1];

            window.speechSynthesis.cancel();
            speechSynthesis.speak(utterance);
        }
    }

    else { 
        /* speech synthesis not supported */
        /*
        msg = document.createElement('h5');
        msg.textContent = "Detected no support for Speech Synthesis";
        msg.style.textAlign = 'center';
        msg.style.backgroundColor = 'red';
        msg.style.color = 'white';
        msg.style.marginTop = msg.style.marginBottom = 0;
        document.body.insertBefore(msg, document.querySelector('div'));
        */ 
    }

}
