# 1 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino"
# 2 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino" 2
# 3 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino" 2
# 4 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino" 2
# 5 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino" 2
# 17 "C:\\Users\\gabri\\Desktop\\Laptop-to-pc\\secondo_semestre\\iot\\03-data-flow\\data-collector\\data-collector.ino"
Scheduler sched;

void setup() {
    ProximitySensor *sensor = new ProximitySensor(10, 11);
    BluetoothMsgService* bt =new BluetoothMsgService("BT", 5, 6, 7, 9600);

    ProducerTask* producerTask = new ProducerTask(bt, sensor);
    producerTask->init(5000);

    sched.init(100);
    sched.addTask(producerTask);
}

void loop() {
    sched.schedule();
}
