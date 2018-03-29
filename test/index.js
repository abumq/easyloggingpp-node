const easyloggingpp = require('../');
const ConfigType = easyloggingpp.ConfigType;
const Level = easyloggingpp.Level;

// alternatively you will do
// import 

console.log(`version: ${easyloggingpp.version()}`);

const logger = easyloggingpp.getLogger('mylogger');

console.log('Logger registered');

logger.configure({
    config_file: 'test/easylogging-config.conf'
});

console.log('Logger configured');

logger.info('info log after first config');

console.log('First log logged');

// or you can use config types
logger.configure({
    config: ConfigType.Format,
    value: '%datetime %msg',
});
console.log('Logger reconfigured for type');

logger.info('info log');

// register new logger

const logger2 = easyloggingpp.getLogger('another_logger');
console.log('another_logger registered');

logger2.info('info log');

easyloggingpp.configureAllLoggers({
    config: ConfigType.Format,
    value: '%levshort %datetime %fbase:%line %msg',
});
console.log('reconfigured all loggers');

easyloggingpp.configureAllLoggers({
    level: Level.Debug,
    config: ConfigType.Format,
    value: '%datetime %fbase:%line %msg',
});
console.log('reconfigured all loggers for debug');

// or you can use array

easyloggingpp.configureAllLoggers([
    {
        level: Level.Error,
        config: ConfigType.Format,
        value: '%datetime >> %msg',
    },
    {
        level: Level.Debug,
        config: ConfigType.Format,
        value: '%datetime %fbase:%line %msg',
    }
]);
console.log('reconfigured all loggers for error and debug');

logger.info('after reconfigure');
logger2.info('after reconfigure');
logger2.debug('after reconfigure');
logger2.error('after reconfigure');

