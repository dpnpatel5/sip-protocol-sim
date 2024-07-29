# SIP Message Simulator

## Overview

This project implements a SIP (Session Initiation Protocol) client and server application(example) in C++ using the `osipparser2` library. The application supports various SIP methods such as REGISTER, INVITE, ACK, BYE, CANCEL, UPDATE, REFER, PRACK, SUBSCRIBE, NOTIFY, PUBLISH, MESSAGE, INFO, and OPTIONS.

The SIP client is designed to send SIP requests to any SIP server, allowing you to test the server's functionality and ensure it properly handles SIP messages.

## Features

- **SIP Server**: Handles SIP requests and responses. Supports registration, call setup, and other SIP operations.
- **SIP Client**: Sends SIP requests to the server and processes responses. Supports all standard SIP methods.

## Prerequisites

- `osipparser2` library (for parsing and handling SIP messages)
- `osip2` library (for SIP message handling)

## Installation

### Installing Dependencies

Ensure you have the `osipparser2` and `osip2` libraries installed on your system. If not, you can install them using the following commands:

```bash
sudo apt-get update
osudo apt-get install libosip2-dev libosipparser2-dev
```

## Building the Application
Clone the repository and navigate to the project directory:
```
git clone https://github.com/dpnpatel5/sip-protocol-sim.git
cd sip-protocol-sim
make
```
##Usage
To start the SIP server, use the following command:
```
./bin/sip_server <server-ip> <server-port>
```
Replace <server-ip> with the IP address on which the server should listen, and <server-port> with the port number (e.g., 5060).


Send SIP Messages Using SIP Client:

Use a SIP client to send SIP messages to the server. For example, you can use a command-line SIP client or a SIP testing tool.
```
./bin/sip_client 127.0.0.1 5060
```
