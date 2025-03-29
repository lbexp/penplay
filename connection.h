class Connection {
  public:
    int init();
    void receive(); // TODO: should return streamed data
    void send();
    void close();
};
