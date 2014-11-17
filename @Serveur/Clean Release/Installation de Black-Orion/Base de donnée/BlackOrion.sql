/*
Navicat MySQL Data Transfer

Source Server         : bo
Source Server Version : 50141
Source Host           : localhost:3306
Source Database       : b-o

Target Server Type    : MYSQL
Target Server Version : 50141
File Encoding         : 65001

Date: 2011-10-19 01:45:58
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `comptes`
-- ----------------------------
DROP TABLE IF EXISTS `comptes`;
CREATE TABLE `comptes` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(16) DEFAULT '-',
  `password` varchar(32) DEFAULT '-',
  `accesslevel` smallint(5) unsigned DEFAULT '70',
  `creation` bigint(20) DEFAULT '0',
  `lastlogin` bigint(20) DEFAULT '0',
  `bantime` bigint(20) DEFAULT '0',
  `points` int(10) unsigned DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='by davedevils';

-- ----------------------------
-- Records of accounts
-- ----------------------------

-- ----------------------------
-- Table structure for `characters`
-- ----------------------------
DROP TABLE IF EXISTS `characters`;
CREATE TABLE `characters` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(16) DEFAULT '-',
  `account` int(10) DEFAULT '0',
  `place` tinyint(3) unsigned DEFAULT '0',
  `sex` tinyint(3) unsigned DEFAULT '0',
  `job` tinyint(3) unsigned DEFAULT '0',
  `hairtype` tinyint(3) unsigned DEFAULT '0',
  `haircolor` int(10) DEFAULT '0',
  `facetype` tinyint(3) unsigned DEFAULT '0',
  `exp` bigint(20) unsigned DEFAULT '0',
  `size` smallint(5) unsigned DEFAULT '100',
  `posx` float DEFAULT '6973',
  `posy` float DEFAULT '100',
  `posz` float DEFAULT '3328',
  `world` int(10) unsigned DEFAULT '1',
  `angle` smallint(5) unsigned DEFAULT '0',
  `level` smallint(5) unsigned DEFAULT '1',
  `hp` int(10) unsigned DEFAULT '230',
  `mp` int(10) unsigned DEFAULT '0',
  `fp` int(10) unsigned DEFAULT '0',
  `stat_str` int(10) unsigned DEFAULT '15',
  `stat_sta` int(10) unsigned DEFAULT '15',
  `stat_dex` int(10) unsigned DEFAULT '15',
  `stat_int` int(10) unsigned DEFAULT '15',
  `statpoints` int(10) unsigned DEFAULT '0',
  `penya` int(10) unsigned DEFAULT '0',
  `skills` varchar(1024) DEFAULT '1:0,2:0,3:0',
  `skillpoints` smallint(10) unsigned DEFAULT '0',
  `creation` bigint(20) DEFAULT '0',
  `online` tinyint(3) unsigned DEFAULT '0',
  `pvp` int(11) DEFAULT '0',
  `pk` int(11) DEFAULT '0',
  `disposition` int(11) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of characters
-- ----------------------------

-- ----------------------------
-- Table structure for `items`
-- ----------------------------
DROP TABLE IF EXISTS `items`;
CREATE TABLE `items` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `owner` int(10) DEFAULT '0',
  `type` tinyint(3) unsigned DEFAULT '0',
  `place` smallint(5) unsigned DEFAULT '0',
  `itemid` int(10) unsigned DEFAULT '0',
  `count` smallint(5) unsigned DEFAULT '0',
  `upgrade` smallint(5) unsigned DEFAULT '0',
  `element` tinyint(3) unsigned DEFAULT '0',
  `eleupgrade` tinyint(3) unsigned DEFAULT '0',
  `stats` tinyint(3) unsigned DEFAULT '0',
  `leveldown` tinyint(3) unsigned DEFAULT '0',
  `type0` tinyint(3) unsigned DEFAULT '0',
  `amount0` smallint(6) DEFAULT '0',
  `type1` tinyint(3) unsigned DEFAULT '0',
  `amount1` smallint(6) DEFAULT '0',
  `type2` tinyint(3) unsigned DEFAULT '0',
  `amount2` smallint(6) DEFAULT '0',
  `slot1` int(10) unsigned DEFAULT '0',
  `slot2` int(10) unsigned DEFAULT '0',
  `slot3` int(10) unsigned DEFAULT '0',
  `slot4` int(10) unsigned DEFAULT '0',
  `slot5` int(10) unsigned DEFAULT '0',
  `slot6` int(11) unsigned DEFAULT '0',
  `slot7` int(11) unsigned DEFAULT '0',
  `slot8` int(11) unsigned DEFAULT '0',
  `slot9` int(11) unsigned DEFAULT '0',
  `slot10` int(11) unsigned DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of items
-- ----------------------------

-- ----------------------------
-- Table structure for `mails`
-- ----------------------------
DROP TABLE IF EXISTS `mails`;
CREATE TABLE `mails` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sender` int(11) DEFAULT '0',
  `receiver` int(11) DEFAULT '0',
  `opened` tinyint(3) unsigned DEFAULT '0',
  `time` bigint(20) DEFAULT '0',
  `money` int(11) unsigned DEFAULT '0',
  `item` int(11) DEFAULT '0',
  `title` varchar(255) DEFAULT '',
  `content` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of mails
-- ----------------------------
