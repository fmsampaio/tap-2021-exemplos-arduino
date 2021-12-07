class PushButton {
  private:
    int pino;
    int estadoAtual, ultimoEstado;

  public:

    PushButton(int pino) {
      this->pino = pino;

      pinMode(this->pino, INPUT);

      this->estadoAtual = LOW;
      this->ultimoEstado = LOW;
    }

    bool pressionadoPorPulso(){
      bool returnable = false;

      this->estadoAtual = digitalRead(this->pino);

      if(this->estadoAtual != this->ultimoEstado) {
        if(this->estadoAtual == HIGH) {
          returnable = true;
        }
        delay(50);
      }
      this->ultimoEstado = this->estadoAtual;
      return returnable;
    }
    bool pressionadoPorNivel(){
      return (digitalRead(this->pino) == LOW ? false : true);
    }
};
