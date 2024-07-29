# Define the compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O2
LDFLAGS =  -losipparser2 -losip2

# Define the directories for source files and output binaries
SERVER_SRC_DIR = ./server
CLIENT_SRC_DIR = ./client
BIN_DIR = bin

# Define the source files for server and client
SERVER_SRC = $(SERVER_SRC_DIR)/SIPParser.cpp $(SERVER_SRC_DIR)/SIPServer.cpp $(SERVER_SRC_DIR)/main_server.cpp
CLIENT_SRC = $(CLIENT_SRC_DIR)/SIPClient.cpp $(CLIENT_SRC_DIR)/main_client.cpp

# Define the output binaries
SERVER_BIN = $(BIN_DIR)/sip_server
CLIENT_BIN = $(BIN_DIR)/sip_client

# Define the targets
all: $(SERVER_BIN) $(CLIENT_BIN)

# Rule to build the server
$(SERVER_BIN): $(SERVER_SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(SERVER_BIN) $(SERVER_SRC) $(LDFLAGS)


# Rule to build the client
$(CLIENT_BIN): $(CLIENT_SRC)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_BIN) $(CLIENT_SRC)

# Rule to clean up build artifacts
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean

