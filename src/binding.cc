//
//  binding.cc
//  Easylogging++ Node.js Binding
//
//  Copyright (C) 2017-present Muflihun Labs
//  Copyright (C) 2017-present @abumusamq
//
//  https://muflihun.com/
//  https://github.com/muflihun/easyloggingpp-node/
//
//  See https://github.com/muflihun/easyloggingpp-node/blob/master/LICENSE
//  for licensing information
//

#include <nan.h>
#include <easylogging++.h>

using v8::FunctionTemplate;
using v8::Isolate;
using v8::String;
using Nan::To;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

INITIALIZE_EASYLOGGINGPP

NAN_METHOD(Version)
{
    info.GetReturnValue().Set(String::NewFromUtf8(Isolate::GetCurrent(), el::VersionInfo::version().c_str()));
}

NAN_METHOD(AddFlag)
{

    String::Utf8Value flagParam(info[0]->ToString());
    std::string flag(*flagParam);
    el::LoggingFlag loggingFlag(static_cast<el::LoggingFlag>(stoi(flag)));

    el::Loggers::addFlag(loggingFlag);
}

NAN_METHOD(RemoveFlag)
{
    String::Utf8Value flagParam(info[0]->ToString());
    std::string flag(*flagParam);
    el::LoggingFlag loggingFlag(static_cast<el::LoggingFlag>(stoi(flag)));

    el::Loggers::removeFlag(loggingFlag);
}

NAN_METHOD(HasFlag)
{
    String::Utf8Value flagParam(info[0]->ToString());
    std::string flag(*flagParam);
    el::LoggingFlag loggingFlag(static_cast<el::LoggingFlag>(stoi(flag)));

    bool has = el::Loggers::hasFlag(loggingFlag);

    info.GetReturnValue().Set(has ? Nan::True() : Nan::False());
}

NAN_METHOD(RegisterLogger)
{
    String::Utf8Value loggerIdParam(info[0]->ToString());
    std::string loggerId(*loggerIdParam);
    el::Loggers::getLogger(loggerId, true);
}

NAN_METHOD(ConfigureFromFile)
{
    String::Utf8Value loggerIdParam(info[0]->ToString());
    std::string loggerId(*loggerIdParam);
    String::Utf8Value fileParam(info[1]->ToString());
    std::string file(*fileParam);

    el::Configurations conf(file);
    el::Logger* logger = el::Loggers::getLogger(loggerId, true);
    el::Loggers::reconfigureLogger(logger, conf);
}

NAN_METHOD(ConfigureValue)
{
    String::Utf8Value loggerIdParam(info[0]->ToString());
    std::string loggerId(*loggerIdParam);

    String::Utf8Value configTypeParam(info[1]->ToString());
    std::string configType(*configTypeParam);

    String::Utf8Value valueParam(info[2]->ToString());
    std::string value(*valueParam);

    el::ConfigurationType config(static_cast<el::ConfigurationType>(stoi(configType)));
    el::Logger* logger = el::Loggers::getLogger(loggerId, true);
    el::Loggers::reconfigureLogger(logger->id(), config, value);
}

NAN_METHOD(ConfigureAllFromFile)
{
    String::Utf8Value fileParam(info[0]->ToString());
    std::string file(*fileParam);

    el::Configurations conf(file);
    el::Loggers::setDefaultConfigurations(conf, true);
}

NAN_METHOD(ConfigureAllValue)
{
    String::Utf8Value configTypeParam(info[0]->ToString());
    std::string configType(*configTypeParam);

    String::Utf8Value valueParam(info[1]->ToString());
    std::string value(*valueParam);

    el::ConfigurationType config(static_cast<el::ConfigurationType>(stoi(configType)));
    el::Loggers::reconfigureAllLoggers(config, value);
}

NAN_METHOD(ConfigureAllValueByLevel)
{
    String::Utf8Value levelTypeParam(info[0]->ToString());
    std::string levelType(*levelTypeParam);

    String::Utf8Value configTypeParam(info[1]->ToString());
    std::string configType(*configTypeParam);

    String::Utf8Value valueParam(info[2]->ToString());
    std::string value(*valueParam);

    el::Level level(static_cast<el::Level>(stoi(levelType)));
    el::ConfigurationType config(static_cast<el::ConfigurationType>(stoi(configType)));
    el::Loggers::reconfigureAllLoggers(level, config, value);
}

NAN_METHOD(WriteLog) {
    String::Utf8Value paramLoggerId(info[0]->ToString());
    String::Utf8Value paramFile(info[1]->ToString());
    String::Utf8Value paramLine(info[2]->ToString());
    String::Utf8Value paramFunc(info[3]->ToString());
    String::Utf8Value paramMsg(info[4]->ToString());
    String::Utf8Value paramLevel(info[5]->ToString());
    String::Utf8Value paramVLevel(info[6]->ToString());
    std::string loggerId(*paramLoggerId);
    std::string file(*paramFile);
    std::string line(*paramLine);
    std::string func(*paramFunc);
    std::string msg(*paramMsg);
    std::string level(*paramLevel);
    std::string vlevel(*paramVLevel);
    el::base::type::LineNumber lineNumb = 0;
    if (line != "undefined" && line != "null") {
        lineNumb = stoi(line);
    }
    el::Level lvl = static_cast<el::Level>(stoi(level));
    el::base::type::VerboseLevel vl = 0;
    if (vlevel != "undefined" && vlevel != "null") {
        vl = stoi(vlevel);
    }
    el::base::Writer(lvl,
                     file.c_str(),
                     lineNumb, func.c_str(),
                     el::base::DispatchAction::NormalLog, vl)
    .construct(1, loggerId.c_str()) << msg;
}

NAN_MODULE_INIT(InitAll)
{
    el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
    el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);

    #define DEFINE_FN(name, callback) Set(target, New<String>(#name).ToLocalChecked(), \
        GetFunction(New<FunctionTemplate>(callback)).ToLocalChecked())

    DEFINE_FN(version, Version);
    DEFINE_FN(configure_from_file, ConfigureFromFile);
    DEFINE_FN(configure, ConfigureValue);
    DEFINE_FN(configure_all_loggers_from_file, ConfigureAllFromFile);
    DEFINE_FN(configure_all_loggers, ConfigureAllValue);
    DEFINE_FN(configure_all_loggers_by_level, ConfigureAllValueByLevel);
    DEFINE_FN(write_log, WriteLog);
    DEFINE_FN(register_logger, RegisterLogger);
    DEFINE_FN(add_flag, AddFlag);
    DEFINE_FN(remove_flag, RemoveFlag);
    DEFINE_FN(has_flag, HasFlag);
    #undef DEFINE_FN
}


NODE_MODULE(easyloggingpp, InitAll)
