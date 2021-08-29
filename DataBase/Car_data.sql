DROP DATABASE  /*!32312 IF EXISTS*/`Cardb` ;
CREATE DATABASE `Cardb`;
USE `Cardb`;

DROP TABLE IF EXISTS Configuration;
CREATE TABLE Configuration (	
	model VARCHAR(255) NOT NULL PRIMARY KEY,
	brand VARCHAR(255) NOT NULL,
	engine_capacity DECIMAL(10,2) NOT NULL comment '发动机排量（单位：升）'
);

insert into Configuration values
('哈弗H2','哈弗','1.5'),
('哈弗H6','哈弗','1.5'),
('哈弗H7','哈弗','2.0'),
('哈弗H9','哈弗','2.0'),
('VV5','WEY','1.5'),
('VV6','WEY','2.0'),
('VV7','WEY','2.0'),
('探索者','坦克','2.0'),
('挑战者','坦克','2.0')
;


DROP TABLE IF EXISTS Car;
CREATE TABLE Car (
	VIN VARCHAR(32) NOT NULL UNIQUE PRIMARY KEY,
	production_date DATE NOT NULL comment '生产日期',
	model VARCHAR(255) NOT NULL,
    color VARCHAR(255) NOT NULL
);

insert into Car values
('USUMS50791529TBMB','2018-01-02','哈弗H2','black'),
('43O23BJDFBWUOEBOW','2018-01-03','哈弗H2','gray'),
('WEUBFDIWEIWOERI23','2018-01-04','哈弗H2','red'),
('129DB84398B129819','2018-04-02','vv5','blue'),
('1298EBD823B0WE023','2018-04-03','vv5','white'),
('239238FW89B32812U','2018-06-02','探索者','black'),
('U23FU923923F0WF23','2019-07-02','哈弗H6','orange'),
('B4GN840GN920N302G','2019-07-03','哈弗H6','gray'),
('UVSU9323B9F8W3SDB','2019-09-02','哈弗H7','blue'),
('239S9B2039TN02FN0','2019-10-02','VV6','red'),
('U2238DB923892RB9R','2019-10-03','VV6','white'),
('U239H9832B9WDSDFR','2019-12-02','探索者','black'),
('VB8W9E0NVE0RNGN3G','2020-01-02','哈弗H7','black'),
('39FB89490FNB0N0WN','2020-02-03','哈弗H7','blue'),
('2398HDF0EF0NEG0N0','2020-03-02','VV7','gray'),
('9SN0EGB8DOSBZSF99','2020-03-04','VV7','black'),
('V9R034JD0NW04HSDN','2020-03-05','VV7','white'),
('F9840IDJN042N9D8W','2020-06-02','挑战者','blue'),
('D9B49F9DJF03JSDIN','2021-01-02','哈弗H7','red'),
('S9BUDB34SID0WNDFS','2021-02-02','哈弗H7','black'),
('23B89SDNF200DFMO2','2021-03-02','VV6','white'),
('UD8923B9SDJ240TNS','2021-04-02','VV7','gray');


DROP TABLE IF EXISTS Components;
CREATE TABLE Components (
	cid INT NOT NULL comment '零件编号',
	model VARCHAR(255) NOT NULL,
	`name` VARCHAR(255) NOT NULL,
	`type` VARCHAR(64) NOT NULL,
	supplier VARCHAR(255) comment '供应商',
	offer_date DATE NOT NULL comment '组装日期'
);

insert into Components values
(1,'哈弗H2','变速器','B1','Getrag','2018-01-02'),
(1,'哈弗H6','变速器','B2','bansuti','2019-07-02'),
(2,'哈弗H2','制动器','Z1','zhid','2018-01-02'),
(3,'哈弗H2','发动机','F1','fadoy','2018-01-02'),
(1,'VV6','变速器','B1','bansuti','2019-10-02'),
(1,'VV7','变速器','B2','bansuti','2020-03-02'),
(2,'探索者','制动器','Z2','zhid','2018-06-02'),
(2,'挑战者','制动器','Z3','zhid','2020-06-02'),
(3,'挑战者','发动器','F2','fadoy','2020-06-02')
;

DROP TABLE IF EXISTS Customer;
CREATE TABLE Customer (
	pid INT NOT NULL PRIMARY KEY,
	`name` VARCHAR(255) NOT NULL,
	sex VARCHAR(6) NOT NULL,
	address VARCHAR(255),
	telephone VARCHAR(20),
	yearly_income DECIMAL(10,2) default  NULL comment '单位：万元',
    check(sex in('男','女'))
);

insert into Customer values
(1,'冯弘深','男','成都','12327391834',8),
(2,'惠哲彦','男','北京','16431312112',176),
(3,'国承平','男','南京','11984181219',283),
(4,'廖立诚','男','上海','14712891781',67),
(5,'衡开霁','男','深圳','11298149811',23),
(6,'芮博','男','广州','18391689241',78),
(7,'刘昕昕','女','香港','11827189328',19),
(8,'容芸英','女','杭州','11892178912',189),
(9,'韶煊悦','女','武汉','18312111334',59),
(10,'蒙红','女','重庆','14782340239',76),
(11,'高雁','女','天津','13989448968',33),
(12,'张三','男','成都','18983434892',21);

DROP TABLE IF EXISTS Dealers;
CREATE TABLE Dealers (
	sid INT NOT NULL primary KEY COMMENT'经销商编号',
	dealer VARCHAR(255) NOT NULL comment '经销商',
    address VARCHAR(255) NOT NULL
);
insert into Dealers values
(1,'havaler','成都'),
(2,'weyer','北京'),
(3,'tanker','上海'),
(4,'havalo','成都'),
(5,'way','北京')
;


DROP TABLE IF EXISTS Remains;
CREATE TABLE Remains (
	sid INT NOT NULL COMMENT'经销商编号',
    model VARCHAR(255) NOT NULL,
    price DECIMAL(10,2) NOT NULL comment '单位（万元）',
    remain INT NOT NULL COMMENT'库存'
);

insert into Remains values
(1,'哈弗H2',8.5,3),
(1,'哈弗H6',10,4),
(1,'哈弗H7',12,5),
(2,'哈弗H2',8.4,2),
(2,'VV5',13,6),
(2,'VV6',15,4),
(2,'VV7',20,5),
(3,'探索者',21.5,2),
(3,'挑战者',24,1),
(4,'哈弗H2',8.6,4),
(4,'哈弗H9',18,1),
(5,'VV6',14.5,5);


DROP TABLE IF EXISTS Purchase;
CREATE TABLE Purchase (
	VIN VARCHAR(32) NOT NULL comment '汽车编号',
	pid INT NOT NULL comment '客户编号',
	purchase_date DATE NOT NULL comment '采购日期',
    sale_date DATE NOT NULL comment '销售日期',
	price DECIMAL(10,2) default  NULL comment '单位（万元）',
	sid INT NOT NULL COMMENT'经销商编号',
    foreign key (VIN) REFERENCES Car(VIN) ON DELETE RESTRICT ON UPDATE CASCADE
);

insert into Purchase values
('USUMS50791529TBMB',1,'2018-06-01','2018-07-01',9,1),
('F9840IDJN042N9D8W',2,'2020-07-01','2021-01-01',25,3),
('239238FW89B32812U',3,'2018-09-01','2018-12-11',22,3),
('B4GN840GN920N302G',4,'2019-10-01','2020-12-01',12,1),
('WEUBFDIWEIWOERI23',5,'2018-08-15','2018-12-21',8.5,1),
('1298EBD823B0WE023',6,'2018-06-13','2018-07-11',13,2),
('129DB84398B129819',7,'2018-11-01','2019-06-01',9,2),
('V9R034JD0NW04HSDN',8,'2020-09-21','2020-12-11',22,5),
('U2238DB923892RB9R',9,'2019-12-01','2020-02-01',15,2),
('VB8W9E0NVE0RNGN3G',10,'2018-08-15','2018-12-21',15,4),
('S9BUDB34SID0WNDFS',11,'2021-03-01','2021-04-01',14.5,4),
('D9B49F9DJF03JSDIN',12,'2021-01-21','2021-02-11',14,1)
;

CREATE USER 'car'@'%' IDENTIFIED BY '123456';
create user 'custom'@'%' identified by '123456';
grant select on cardb.* to 'car'@'%';
grant select on cardb.* to 'custom'@'%';
