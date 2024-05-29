CREATE DATABASE IF NOT EXISTS db
DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;

use db;

CREATE TABLE IF NOT EXISTS users(
    user_id INTEGER PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL,
    login VARCHAR(50) NOT NULL UNIQUE
    );

CREATE TABLE IF NOT EXISTS passwords (
    user_id INTEGER PRIMARY KEY,
    password_hash VARCHAR(32) NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(user_id)
    );

CREATE TABLE IF NOT EXISTS messages (
    message_id INTEGER PRIMARY KEY AUTO_INCREMENT,
    from_id INTEGER NOT NULL,
    to_id INTEGER NOT NULL,
    message TEXT CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
    FOREIGN KEY (from_id) REFERENCES users(user_id),
    FOREIGN KEY (to_id) REFERENCES users(user_id)
    ) CHARACTER SET utf8;

INSERT INTO users(name, login) VALUES
 ('All', 'All'),
 ('Ivan', 'Iv'),
 ('Alexey', 'Al'),
 ('Marina', 'Ma');
   
-- 2360484733 хэш пароля 12345 
INSERT INTO passwords(user_id, password_hash) VALUES
    (1, '2360484733'),
    (2, '2360484733'),
    (3, '2360484733'),
    (4, '2360484733');

INSERT INTO messages(from_id, to_id, message) VALUES 
    (2, 1, 'Hello'),
    (3 ,1 ,'Good morning'),
    (2 ,3 ,'Good evening'),
    (3 ,2 ,'How are you'),
    (2 ,3 ,'I am fine'),
    (4 ,1 ,'message is good');
