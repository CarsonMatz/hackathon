#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* The sign in credentials */
#define AUTHOR_EMAIL "gas.sensor.warning@gmail.com"
#define AUTHOR_PASSWORD "hackathon"

/* Recipient's email*/
#define RECIPIENT_EMAIL "tjhayes@usc.edu"

/* The SMTP Session object used for Email sending */
SMTPSession smtp;

void smtpCallback(SMTP_Status status);

void setup() {
  // put your setup code here, to run once:
  const char* ssid = "Carson's iPhone";
  const char* password = "12345678";
  initWifi();

  smtp.debug(1);
  
  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);
  
  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;

  /* Set the message headers */
  message.sender.name = "Blueberry Pi";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Carbon Dioxide Warning";
  message.addRecipient("Taiyo", RECIPIENT_EMAIL);

  String textMsg = "Carbon Dioxide levels are dangerously high. Take warning.";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
}

void loop() {
  // put your main code here, to run repeatedly:
  /* Callback function to get the Email sending status */
  void smtpCallback(SMTP_Status status){

}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

kgystygpuwxvjfpr
