const easyloggingpp = require('easyloggingpp');
const ConfigType = easyloggingpp.ConfigType;
const Level = easyloggingpp.Level;

// alternatively you will do
// import 

const logger = easyloggingpp.getLogger('mylogger');

logger.configure({
    config_file: 'default.conf'
});

// or you can use config types
logger.configure({
    config: ConfigType.Format,
    value: '%datetime %msg',
});

logger.info('info log');

// register new logger

const logger2 = easyloggingpp.getLogger('another logger');

logger2.info('info log');

easyloggingpp.configureAllLoggers({
    config: ConfigType.Format,
    value: '%levshort %datetime %fbase:%line %msg',
});

easyloggingpp.configureAllLoggers({
    level: Level.Debug,
    config: ConfigType.Format,
    value: '%datetime %fbase:%line %msg',
});

logger.info('after reconfigure');
logger2.info('after reconfigure');
logger2.debug('after reconfigure');