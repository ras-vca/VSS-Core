//
// Created by johnathan on 01/07/18.
//

#include <iostream>
#include <Interpreters/StdinInterpreter.h>
#include <Domain/ExecutionConfig.h>
#include <Domain/Constants.h>

namespace vss {

    StdinInterpreter::StdinInterpreter() {
        onStateRecvAddr = false;
        onStateSendAddr = false;

        onYellowCmdRecvAddr = false;
        onYellowCmdSendAddr = false;
        onYellowDebugRecvAddr = false;
        onYellowDebugSendAddr = false;

        onBlueCmdRecvAddr = false;
        onBlueCmdSendAddr = false;
        onBlueDebugRecvAddr = false;
        onBlueDebugSendAddr = false;

        onCtrlRecvAddr = false;
        onCtrlSendAddr = false;

        onStatePort = false;
        onYellowCmdPort = false;
        onYellowDebugPort = false;
        onBlueCmdPort = false;
        onBlueDebugPort = false;
        onCtrlPort = false;

        onTeamType = false;
        onSideAttackType = false;
        onTimeExecutionType = false;
        onEnvironmentType = false;

        stdinConfiguration.isValidConfiguration = false;
    }

    ExecutionConfig StdinInterpreter::extractExecutionConfig(int argc, char **argv) {
        try
        {
            auto desc = buildOptions();

            boost::program_options::variables_map vm;
            store(parse_command_line(argc, argv, desc), vm);
            notify(vm);

            if (vm.count("help")){
                std::cout << desc << '\n';
                return stdinConfiguration;
            }

            buildConfiguration(vm);

            return stdinConfiguration;
        }
        catch (const boost::program_options::error &ex)
        {
            std::cerr << ex.what() << '\n';
        }


        return stdinConfiguration;
    }

    boost::program_options::options_description StdinInterpreter::buildOptions() {
        boost::program_options::options_description desc{"Options"};

        desc.add_options()("help,h", "");

        // ADDRESS
        if(onStateSendAddr)
            desc.add_options()("state_send_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_STATE_SEND_ADDR), "");

        if(onStateRecvAddr)
            desc.add_options()("state_recv_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_STATE_RECV_ADDR), "");

        if(onYellowCmdSendAddr)
            desc.add_options()("yellow_cmd_send_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_CMD_SEND_ADDR), "");

        if(onYellowCmdRecvAddr)
            desc.add_options()("yellow_cmd_recv_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_CMD_RECV_ADDR), "");

        if(onYellowDebugSendAddr)
            desc.add_options()("yellow_debug_send_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_DEBUG_SEND_ADDR), "");

        if(onYellowDebugRecvAddr)
            desc.add_options()("yellow_debug_recv_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_DEBUG_RECV_ADDR), "");

        if(onBlueCmdSendAddr)
            desc.add_options()("blue_cmd_send_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_CMD_SEND_ADDR), "");

        if(onBlueCmdRecvAddr)
            desc.add_options()("blue_cmd_recv_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_CMD_RECV_ADDR), "");

        if(onBlueDebugSendAddr)
            desc.add_options()("blue_debug_send_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_DEBUG_SEND_ADDR), "");

        if(onBlueDebugRecvAddr)
            desc.add_options()("blue_debug_recv_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_DEBUG_RECV_ADDR), "");

        if(onCtrlSendAddr)
            desc.add_options()("ctrl_send_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_CTRL_SEND_ADDR), "");

        if(onCtrlRecvAddr)
            desc.add_options()("ctrl_recv_addr", boost::program_options::value<std::string>()->default_value(DEFAULT_CTRL_RECV_ADDR), "");


        // PORTS
        if(onStatePort)
            desc.add_options()("state_port", boost::program_options::value<int>()->default_value(DEFAULT_STATE_PORT), "");

        if(onYellowCmdPort)
            desc.add_options()("yellow_cmd_port", boost::program_options::value<int>()->default_value(DEFAULT_CMD_YELLOW_PORT), "");

        if(onBlueCmdPort)
            desc.add_options()("blue_cmd_port", boost::program_options::value<int>()->default_value(DEFAULT_CMD_BLUE_PORT), "");

        if(onYellowDebugPort)
            desc.add_options()("yellow_debug_port", boost::program_options::value<int>()->default_value(DEFAULT_DEBUG_YELLOW_PORT), "");

        if(onBlueDebugPort)
            desc.add_options()("blue_debug_port", boost::program_options::value<int>()->default_value(DEFAULT_DEBUG_BLUE_PORT), "");

        if(onCtrlPort)
            desc.add_options()("ctrl_port", boost::program_options::value<int>()->default_value(DEFAULT_CTRL_PORT), "");


        // Types
        if(onTeamType)
            desc.add_options()("team_type", boost::program_options::value<std::string>()->default_value(toDescription(DEFAULT_TEAM_TYPE)), "");

        if(onSideAttackType)
            desc.add_options()("side_attack_type", boost::program_options::value<std::string>()->default_value(toDescription(DEFAULT_SIDE_ATTACK_TYPE)), "");

        if(onTimeExecutionType)
            desc.add_options()("time_execution_type", boost::program_options::value<std::string>()->default_value(toDescription(DEFAULT_TIME_EXECUTION_TYPE)), "");

        if(onEnvironmentType)
            desc.add_options()("environment_type", boost::program_options::value<std::string>()->default_value(toDescription(DEFAULT_ENVIRONMENT_TYPE)), "");


        return desc;
    }

    void StdinInterpreter::buildConfiguration(boost::program_options::variables_map vm) {
        // ADDRESS
        if(vm.count("state_send_addr"))
            stdinConfiguration.stateSendAddr.setIp(vm["state_send_addr"].as<std::string>());

        if(vm.count("state_recv_addr"))
            stdinConfiguration.stateRecvAddr.setIp(vm["state_recv_addr"].as<std::string>());

        if(vm.count("yellow_cmd_send_addr"))
            stdinConfiguration.cmdYellowSendAddr.setIp(vm["yellow_cmd_send_addr"].as<std::string>());

        if(vm.count("yellow_cmd_recv_addr"))
            stdinConfiguration.cmdYellowRecvAddr.setIp(vm["yellow_cmd_recv_addr"].as<std::string>());

        if(vm.count("yellow_debug_send_addr"))
            stdinConfiguration.debugYellowSendAddr.setIp(vm["yellow_debug_send_addr"].as<std::string>());

        if(vm.count("yellow_debug_recv_addr"))
            stdinConfiguration.debugYellowRecvAddr.setIp(vm["yellow_debug_recv_addr"].as<std::string>());

        if(vm.count("blue_cmd_send_addr"))
            stdinConfiguration.cmdBlueSendAddr.setIp(vm["blue_cmd_send_addr"].as<std::string>());

        if(vm.count("blue_cmd_recv_addr"))
            stdinConfiguration.cmdBlueRecvAddr.setIp(vm["blue_cmd_recv_addr"].as<std::string>());

        if(vm.count("blue_debug_send_addr"))
            stdinConfiguration.debugBlueSendAddr.setIp(vm["blue_debug_send_addr"].as<std::string>());

        if(vm.count("blue_debug_recv_addr"))
            stdinConfiguration.debugBlueRecvAddr.setIp(vm["blue_debug_recv_addr"].as<std::string>());


        // PORTS
        if(vm.count("state_port")){
            stdinConfiguration.stateSendAddr.setPort(vm["state_port"].as<int>());
            stdinConfiguration.stateRecvAddr.setPort(vm["state_port"].as<int>());
        }

        if(vm.count("yellow_cmd_port")){
            stdinConfiguration.cmdYellowSendAddr.setPort(vm["yellow_cmd_port"].as<int>());
            stdinConfiguration.cmdYellowRecvAddr.setPort(vm["yellow_cmd_port"].as<int>());
        }

        if(vm.count("blue_cmd_port")){
            stdinConfiguration.cmdBlueSendAddr.setPort(vm["blue_cmd_port"].as<int>());
            stdinConfiguration.cmdBlueRecvAddr.setPort(vm["blue_cmd_port"].as<int>());
        }

        if(vm.count("yellow_debug_port")){
            stdinConfiguration.debugYellowSendAddr.setPort(vm["yellow_debug_port"].as<int>());
            stdinConfiguration.debugYellowRecvAddr.setPort(vm["yellow_debug_port"].as<int>());
        }

        if(vm.count("blue_debug_port")){
            stdinConfiguration.debugBlueSendAddr.setPort(vm["blue_debug_port"].as<int>());
            stdinConfiguration.debugBlueRecvAddr.setPort(vm["blue_debug_port"].as<int>());
        }

        if(vm.count("ctrl_port")){
            stdinConfiguration.ctrlSendAddr.setPort(vm["ctrl_port"].as<int>());
            stdinConfiguration.ctrlRecvAddr.setPort(vm["ctrl_port"].as<int>());
        }


        // TYPES
        if(vm.count("team_type"))
            stdinConfiguration.teamType = toTeamType(vm["team_type"].as<std::string>());

        if(vm.count("side_attack_type"))
            stdinConfiguration.sideAttackType = toSideAttackType(vm["side_attack_type"].as<std::string>());

        if(vm.count("time_execution_type"))
            stdinConfiguration.timeExecutionType = toTimeExecutionType(vm["time_execution_type"].as<std::string>());

        if(vm.count("environment_type"))
            stdinConfiguration.environmentType = toEnvironmentType(vm["environment_type"].as<std::string>());


        stdinConfiguration.isValidConfiguration = true;
    }

};