#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

class server {
private:
    const float OffsetFromPredicted {0.0f};
public:
    int runServer();
    void sendMessage();
};

#endif // SERVER_H_INCLUDED
