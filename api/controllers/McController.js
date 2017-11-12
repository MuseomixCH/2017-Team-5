const Audio = require("audio");

var nbDevicesOn = 0;

exports.deviceOn = function (req, res) {
    nbDevicesOn++;

    var audio = new Audio('../music/audio.wav');
   
    audio.play();

    res.json("it's on with " + nbDevicesOn + " devices");
};

exports.deviceOff = function (req, res) {
    if (nbDevicesOn > 0) {
        nbDevicesOn--;
    }
    res.json("it's off with " + nbDevicesOn + " devices");
}