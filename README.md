# cpp-redis
Miniature Redis implementation in c++ to deep dive into the language.


g++ --std=c++11 -o server main.cpp redisObj.cpp store.cpp cmd.cpp eval.cpp ../utils/string_utility.cpp handle_connection.cpp

g++ --std=c++11 -o client main.cpp ../utils/string_utility.cpp