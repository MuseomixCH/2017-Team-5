'use strict';
module.exports = function(app) {
  var Mc = require('../controllers/McController');

  app.route('/deviceOn/:deviceId')
    .get(Mc.deviceOn);

    app.route('/deviceOff/:deviceId')
    .get(Mc.deviceOff);
};