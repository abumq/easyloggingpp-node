const easyloggingpp = require('easyloggingpp');
const ConfigType = easyloggingpp.ConfigType;
const Level = easyloggingpp.Level;
const logger = easyloggingpp.getLogger('mylogger'); // register logger

easyloggingpp.configureAllLoggers([
    {
        config: ConfigType.Format,
        value: '%levshort %datetime %fbase:%line %msg',  // <-- fbase or file for full path 
    },
    {
        config: ConfigType.Filename,
        value: 'logs/output.log'
    }
]);

// alternatively you can use following to set default configurations
// for future loggers as well as existing logger
easyloggingpp.configureAllLoggers({
    config_file: 'easylogging-config.conf',
});

logger.info('simple log');
logger.info('array %s', [1, 2, 3]);
var person = { 'name': 'Adam', 'age': 960, }
logger.info('obj %s', person);

logger.error('an error occurred %s', new Error("error msg"));

easyloggingpp.setLogErrorStack(false);
logger.error('an error occurred %s', new Error("error msg"));
