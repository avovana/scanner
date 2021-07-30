namespace cpp slave_controller

enum ScannerStatus {
  Ready = 1,
  Stop = 2
}

service SlaveController {
   void scanner_status(1:ScannerStatus status),
   void scan(1:string scan)
}