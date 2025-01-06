-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Εξυπηρετητής: mysql
-- Χρόνος δημιουργίας: 06 Ιαν 2025 στις 16:14:32
-- Έκδοση διακομιστή: 8.0.40
-- Έκδοση PHP: 8.2.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Βάση δεδομένων: `smartcamp`
--

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `ACCOMODATION_SPOT`
--

CREATE TABLE `ACCOMODATION_SPOT` (
  `suid` int NOT NULL,
  `commercial_name` varchar(255) NOT NULL,
  `class_name` varchar(255) NOT NULL,
  `class_type` enum('TENT','RV','BUNGALOW') NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `ACCOMODATION_SPOT`
--

INSERT INTO `ACCOMODATION_SPOT` (`suid`, `commercial_name`, `class_name`, `class_type`) VALUES
(101, '', 'RV_beach', 'RV'),
(102, '', 'RV_beach', 'RV'),
(103, '', 'RV_beach', 'RV'),
(104, '', 'RV_beach', 'RV'),
(111, '', 'RV_forest', 'RV'),
(112, '', 'RV_forest', 'RV'),
(113, '', 'RV_forest', 'RV'),
(114, '', 'RV_forest', 'RV'),
(121, '', 'RV_hill', 'RV'),
(122, '', 'RV_hill', 'RV'),
(123, '', 'RV_hill', 'RV'),
(124, '', 'RV_hill', 'RV'),
(201, '', 'BUNGALOW_beach', 'BUNGALOW'),
(202, '', 'BUNGALOW_beach', 'BUNGALOW'),
(203, '', 'BUNGALOW_beach', 'BUNGALOW'),
(204, '', 'BUNGALOW_beach', 'BUNGALOW'),
(205, '', 'BUNGALOW_beach', 'BUNGALOW'),
(211, '', 'BUNGALOW_forest', 'BUNGALOW'),
(212, '', 'BUNGALOW_forest', 'BUNGALOW'),
(213, '', 'BUNGALOW_forest', 'BUNGALOW'),
(214, '', 'BUNGALOW_forest', 'BUNGALOW'),
(221, '', 'BUNGALOW_hill', 'BUNGALOW'),
(222, '', 'BUNGALOW_hill', 'BUNGALOW'),
(223, '', 'BUNGALOW_hill', 'BUNGALOW'),
(301, '', 'TENT_beach', 'TENT'),
(302, '', 'TENT_beach', 'TENT'),
(303, '', 'TENT_beach', 'TENT'),
(304, '', 'TENT_beach', 'TENT'),
(305, '', 'TENT_beach', 'TENT'),
(306, '', 'TENT_beach', 'TENT'),
(307, '', 'TENT_beach', 'TENT'),
(308, '', 'TENT_beach', 'TENT'),
(309, '', 'TENT_beach', 'TENT'),
(311, '', 'TENT_forest', 'TENT'),
(312, '', 'TENT_forest', 'TENT'),
(313, '', 'TENT_forest', 'TENT'),
(314, '', 'TENT_forest', 'TENT'),
(315, '', 'TENT_forest', 'TENT'),
(316, '', 'TENT_forest', 'TENT'),
(317, '', 'TENT_forest', 'TENT'),
(318, '', 'TENT_forest', 'TENT'),
(319, '', 'TENT_forest', 'TENT'),
(321, '', 'TENT_forest', 'TENT'),
(322, '', 'TENT_forest', 'TENT'),
(323, '', 'TENT_forest', 'TENT'),
(324, '', 'TENT_forest', 'TENT'),
(325, '', 'TENT_forest', 'TENT'),
(326, '', 'TENT_forest', 'TENT'),
(327, '', 'TENT_forest', 'TENT'),
(328, '', 'TENT_forest', 'TENT'),
(329, '', 'TENT_forest', 'TENT');

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `BUNGALOW`
--

CREATE TABLE `BUNGALOW` (
  `suid` int NOT NULL,
  `max_persons` int NOT NULL,
  `buid` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `BUNGALOW`
--

INSERT INTO `BUNGALOW` (`suid`, `max_persons`, `buid`) VALUES
(201, 2, 1),
(202, 3, 2),
(203, 2, 3),
(204, 3, 4),
(205, 3, 5),
(211, 2, 11),
(212, 3, 12),
(213, 2, 13),
(214, 3, 14),
(221, 3, 21),
(222, 3, 22),
(223, 3, 23);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `CONTAINED_CUSTOMER`
--

CREATE TABLE `CONTAINED_CUSTOMER` (
  `cuid` int NOT NULL,
  `ruid` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `CONTAINED_CUSTOMER`
--

INSERT INTO `CONTAINED_CUSTOMER` (`cuid`, `ruid`) VALUES
(15, 397),
(25, 397),
(15, 398),
(25, 398),
(14, 399),
(25, 399),
(14, 400),
(25, 400),
(32, 400),
(15, 401),
(25, 401),
(14, 402),
(15, 402),
(14, 403),
(25, 403),
(15, 407),
(25, 407),
(15, 410),
(31, 411),
(32, 411),
(36, 413),
(39, 415),
(40, 415),
(43, 417),
(25, 418),
(34, 420),
(37, 422),
(40, 424),
(41, 424);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `CUSTOMER`
--

CREATE TABLE `CUSTOMER` (
  `cuid` int NOT NULL,
  `first_name` varchar(255) NOT NULL,
  `middle_name` varchar(255) DEFAULT NULL,
  `last_name` varchar(255) NOT NULL,
  `tel_country` varchar(4) DEFAULT '0030',
  `tel_num` bigint UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `CUSTOMER`
--

INSERT INTO `CUSTOMER` (`cuid`, `first_name`, `middle_name`, `last_name`, `tel_country`, `tel_num`) VALUES
(14, 'DIMITRIOS', 'MIDNAME', 'SGOURAKIS', '30', 6970217035),
(15, 'SOTIRIS', NULL, 'SVERONIS', '30', 123456789),
(25, 'Ethan', NULL, 'Thompson', '0030', NULL),
(31, 'Ching-Tsung', NULL, 'Tsai', '0030', NULL),
(32, 'BASILIS', NULL, 'BALAKIS', '0030', NULL),
(34, 'Sophia', NULL, 'Carter', '001', 2345678901),
(35, 'Liam', NULL, 'Mitchell', NULL, NULL),
(36, 'Olivia', NULL, 'White', '030', 4159876543),
(37, 'Noah', NULL, 'Brown', NULL, NULL),
(38, 'Emma', NULL, 'Davis', NULL, NULL),
(39, 'Lucas', NULL, 'Martinez', '030', 7863456789),
(40, 'Ava', NULL, 'Gonzalez', NULL, NULL),
(41, 'Mason', NULL, 'Lee', '030', 2024567890),
(42, 'Isabella', NULL, 'Perez', NULL, NULL),
(43, 'Ethan', NULL, 'King', '001', 3126781234),
(44, 'James', NULL, 'Porter', NULL, NULL),
(45, 'Emma', NULL, 'Walsh', '0030', 5125552890),
(46, 'Oliver', NULL, 'Green', NULL, NULL),
(47, 'Sophia', NULL, 'Bennett', '0030', 3055557421),
(48, 'Liam', NULL, 'Collins', NULL, NULL),
(49, 'Ava', NULL, 'Martinez', '0030', 9175553245),
(50, 'Mason', NULL, 'Hayes', NULL, NULL),
(51, 'Isabella', NULL, 'Ross', '0030', 4155556678),
(52, 'Ethan', NULL, 'Clarke', NULL, NULL),
(53, 'Mia', NULL, 'Foster', '0030', 7025558932);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `INCLUDED_SERVICE`
--

CREATE TABLE `INCLUDED_SERVICE` (
  `service_name` varchar(255) NOT NULL,
  `ruid` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `INCLUDED_SERVICE`
--

INSERT INTO `INCLUDED_SERVICE` (`service_name`, `ruid`) VALUES
('Medium_tent', 379),
('Medium_tent', 400),
('Power', 400),
('Medium_tent', 404);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `PARKING_SPOT`
--

CREATE TABLE `PARKING_SPOT` (
  `letter` varchar(2) NOT NULL,
  `number` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `PARKING_SPOT`
--

INSERT INTO `PARKING_SPOT` (`letter`, `number`) VALUES
('A', 1),
('A', 2),
('A', 3),
('A', 4),
('A', 5),
('A', 6),
('A', 7),
('A', 8),
('B', 1),
('B', 2),
('B', 3),
('B', 4),
('B', 5),
('B', 6),
('B', 7),
('B', 8),
('C', 1),
('C', 2),
('C', 3),
('C', 4),
('C', 5),
('C', 6),
('C', 7),
('C', 8),
('D', 1),
('D', 2),
('D', 3),
('D', 4),
('D', 5),
('D', 6),
('D', 7),
('D', 8),
('E', 1),
('E', 2),
('E', 3),
('E', 4),
('E', 5),
('E', 6),
('E', 7),
('E', 8);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `PAYMENT`
--

CREATE TABLE `PAYMENT` (
  `puid` int NOT NULL,
  `method` enum('CARD','CASH','BANK_TRANSFER','CHEQUE') NOT NULL,
  `amount` decimal(10,0) NOT NULL,
  `date` datetime NOT NULL,
  `ruid` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `PAYMENT`
--

INSERT INTO `PAYMENT` (`puid`, `method`, `amount`, `date`, `ruid`) VALUES
(1, 'CARD', 100, '2024-12-28 16:08:20', 390),
(2, 'CARD', 200, '2024-12-28 16:08:20', 390),
(4, 'CARD', 500, '2024-12-28 16:08:20', 392),
(5, 'CARD', 100, '2025-01-04 14:08:25', 399),
(6, 'CARD', 150, '2025-01-04 14:27:32', 400),
(7, 'CARD', 60, '2025-01-04 22:16:44', 398);

--
-- Δείκτες `PAYMENT`
--
DELIMITER $$
CREATE TRIGGER `check_payment_lte_totalCost` BEFORE INSERT ON `PAYMENT` FOR EACH ROW BEGIN
    DECLARE total_payments DECIMAL(10, 2);
    DECLARE reservation_cost DECIMAL(10, 2);

    -- Calculate the total payments for the reservation
    SELECT COALESCE(SUM(amount), 0) INTO total_payments
    FROM PAYMENT
    WHERE ruid = NEW.ruid;

    -- Get the total cost of the reservation
    SELECT total_cost INTO reservation_cost
    FROM RESERVATION
    WHERE ruid = NEW.ruid;

    -- Check if the new payment would cause the total to exceed the reservation's cost
    IF reservation_cost IS NULL THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Reservation does not exist.';
    ELSEIF total_payments + NEW.amount > reservation_cost THEN
        SIGNAL SQLSTATE '45000'
        SET MESSAGE_TEXT = 'Total payments exceed the reservation cost.';
    END IF;
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `RESERVATION`
--

CREATE TABLE `RESERVATION` (
  `ruid` int NOT NULL,
  `total_cost` decimal(10,0) NOT NULL,
  `checkin_date` date NOT NULL,
  `checkout_date` date NOT NULL,
  `main_cuid` int NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `RESERVATION`
--

INSERT INTO `RESERVATION` (`ruid`, `total_cost`, `checkin_date`, `checkout_date`, `main_cuid`) VALUES
(379, 575, '2024-12-31', '2025-01-07', 15),
(390, 300, '2024-12-28', '2024-12-31', 14),
(391, 384, '2024-12-17', '2024-12-19', 25),
(392, 863, '2023-12-03', '2023-12-05', 14),
(397, 420, '2025-01-04', '2025-01-10', 14),
(398, 60, '2025-02-16', '2025-02-18', 14),
(399, 400, '2025-01-10', '2025-01-15', 31),
(400, 245, '2025-01-30', '2025-02-02', 15),
(401, 864, '2025-05-01', '2025-05-10', 14),
(402, 610, '2025-05-01', '2025-05-10', 25),
(403, 864, '2025-05-01', '2025-05-10', 15),
(404, 200, '2025-05-10', '2025-05-15', 25),
(405, 235, '2025-05-18', '2025-05-20', 25),
(406, 200, '2025-05-18', '2025-05-20', 15),
(407, 120, '2025-02-01', '2025-02-05', 14),
(410, 60, '2025-01-08', '2025-01-10', 14),
(411, 120, '2025-01-09', '2025-01-12', 25),
(412, 135, '2025-01-10', '2025-01-13', 34),
(413, 270, '2025-01-11', '2025-01-14', 35),
(414, 180, '2025-01-12', '2025-01-16', 37),
(415, 140, '2025-01-07', '2025-01-09', 38),
(416, 50, '2025-01-09', '2025-01-14', 41),
(417, 20, '2025-01-10', '2025-01-12', 42),
(418, 40, '2025-02-08', '2025-02-11', 15),
(419, 19, '2025-02-13', '2025-02-15', 31),
(420, 55, '2025-01-06', '2025-01-09', 32),
(421, 40, '2025-01-07', '2025-01-11', 35),
(422, 30, '2025-02-11', '2025-02-14', 36),
(423, 30, '2025-01-12', '2025-01-15', 38),
(424, 335, '2025-02-09', '2025-02-13', 39);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `RESERVED_PARKING`
--

CREATE TABLE `RESERVED_PARKING` (
  `ruid` int NOT NULL,
  `pletter` varchar(2) NOT NULL,
  `pnumber` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `RESERVED_PARKING`
--

INSERT INTO `RESERVED_PARKING` (`ruid`, `pletter`, `pnumber`) VALUES
(379, 'A', 1),
(399, 'A', 1),
(400, 'A', 1),
(401, 'A', 1),
(405, 'A', 1),
(418, 'A', 1),
(390, 'A', 2),
(398, 'A', 2),
(400, 'A', 2),
(401, 'A', 2),
(404, 'A', 2),
(405, 'A', 2),
(413, 'A', 2),
(418, 'A', 2),
(398, 'A', 3),
(402, 'A', 3),
(406, 'A', 3),
(407, 'A', 3),
(413, 'A', 3),
(422, 'A', 3),
(398, 'A', 4),
(402, 'A', 4),
(406, 'A', 4),
(407, 'A', 4),
(414, 'A', 4),
(422, 'A', 4),
(410, 'A', 5),
(419, 'A', 5),
(424, 'A', 5),
(411, 'A', 6),
(424, 'A', 6),
(412, 'A', 7),
(415, 'A', 7),
(424, 'A', 7),
(416, 'A', 8),
(403, 'B', 1),
(407, 'B', 1),
(417, 'B', 1),
(420, 'B', 1),
(417, 'B', 2),
(421, 'B', 3),
(423, 'B', 3);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `RESERVED_SPOT`
--

CREATE TABLE `RESERVED_SPOT` (
  `ruid` int NOT NULL,
  `suid` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `RESERVED_SPOT`
--

INSERT INTO `RESERVED_SPOT` (`ruid`, `suid`) VALUES
(390, 101),
(399, 101),
(401, 101),
(405, 101),
(399, 102),
(401, 102),
(405, 102),
(399, 103),
(403, 103),
(406, 103),
(403, 104),
(406, 104),
(410, 104),
(402, 111),
(402, 112),
(404, 113),
(411, 121),
(411, 122),
(379, 201),
(412, 201),
(379, 202),
(413, 202),
(413, 203),
(414, 204),
(391, 211),
(397, 211),
(424, 211),
(391, 212),
(397, 212),
(400, 212),
(424, 212),
(397, 213),
(400, 213),
(407, 214),
(415, 221),
(415, 222),
(398, 301),
(398, 302),
(398, 303),
(416, 304),
(419, 305),
(407, 311),
(417, 311),
(418, 311),
(420, 311),
(407, 312),
(420, 312),
(392, 314),
(421, 321),
(422, 321),
(423, 321);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `RV_SPOT`
--

CREATE TABLE `RV_SPOT` (
  `suid` int NOT NULL,
  `size` decimal(10,0) NOT NULL,
  `rvid` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `RV_SPOT`
--

INSERT INTO `RV_SPOT` (`suid`, `size`, `rvid`) VALUES
(101, 5, 1),
(102, 5, 2),
(103, 5, 3),
(104, 5, 4),
(111, 5, 11),
(112, 5, 12),
(113, 5, 13),
(114, 5, 14),
(121, 5, 21),
(122, 5, 22),
(123, 5, 23),
(124, 5, 24);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `SERVICE`
--

CREATE TABLE `SERVICE` (
  `name` varchar(255) NOT NULL,
  `cost` decimal(10,0) NOT NULL,
  `description` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `SERVICE`
--

INSERT INTO `SERVICE` (`name`, `cost`, `description`) VALUES
('Firewood1', 5, NULL),
('Firewood2', 10, NULL),
('Giant_tent', 50, 'Giant tent for up to 6 people'),
('Lamp', 5, NULL),
('Large_tent', 40, 'Large tent for 4 people'),
('Medium_tent', 25, 'Medium tent for 2 people'),
('Power', 10, 'Electrical power for the accomodation spot.'),
('Small_tent', 15, 'Small tent for 1 person'),
('Surfboard', 40, NULL);

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `SPOT_CLASS`
--

CREATE TABLE `SPOT_CLASS` (
  `class_name` varchar(255) NOT NULL,
  `class_type` enum('TENT','RV','BUNGALOW') NOT NULL,
  `season` varchar(255) NOT NULL,
  `cost` decimal(10,0) NOT NULL,
  `description` text,
  `start_date` date NOT NULL,
  `end_date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `SPOT_CLASS`
--

INSERT INTO `SPOT_CLASS` (`class_name`, `class_type`, `season`, `cost`, `description`, `start_date`, `end_date`) VALUES
('BUNGALOW_beach', 'BUNGALOW', 'HIGH', 80, NULL, '1970-06-01', '1970-08-31'),
('BUNGALOW_beach', 'BUNGALOW', 'LOW', 45, NULL, '1970-09-01', '1970-05-31'),
('BUNGALOW_forest', 'BUNGALOW', 'HIGH', 80, NULL, '1970-06-01', '1970-08-31'),
('BUNGALOW_forest', 'BUNGALOW', 'LOW', 45, NULL, '1970-09-01', '1970-05-31'),
('BUNGALOW_hill', 'BUNGALOW', 'HIGH', 50, NULL, '1970-06-01', '1970-08-31'),
('BUNGALOW_hill', 'BUNGALOW', 'LOW', 35, NULL, '1970-09-01', '1970-05-31'),
('RV_beach', 'RV', 'HIGH', 45, NULL, '1970-06-01', '1970-08-31'),
('RV_beach', 'RV', 'LOW', 30, NULL, '1970-09-01', '1970-05-31'),
('RV_forest', 'RV', 'HIGH', 45, NULL, '1970-06-01', '1970-08-31'),
('RV_forest', 'RV', 'LOW', 30, NULL, '1970-09-01', '1970-05-31'),
('RV_hill', 'RV', 'HIGH', 35, NULL, '1970-06-01', '1970-08-31'),
('RV_hill', 'RV', 'LOW', 20, NULL, '1970-09-01', '1970-05-31'),
('TENT_beach', 'TENT', 'HIGH', 20, NULL, '1970-06-01', '1970-08-31'),
('TENT_beach', 'TENT', 'LOW', 10, NULL, '1970-09-01', '1970-05-28'),
('TENT_forest', 'TENT', 'HIGH', 20, NULL, '1970-06-01', '1970-08-31'),
('TENT_forest', 'TENT', 'LOW', 10, NULL, '1970-09-01', '1970-05-31'),
('TENT_hill', 'TENT', 'HIGH', 15, NULL, '1970-06-01', '1970-08-31'),
('TENT_hill', 'TENT', 'LOW', 10, NULL, '1970-09-01', '1970-05-31');

-- --------------------------------------------------------

--
-- Δομή πίνακα για τον πίνακα `TENT_SPACE`
--

CREATE TABLE `TENT_SPACE` (
  `suid` int NOT NULL,
  `size` decimal(10,0) NOT NULL,
  `tid` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- Άδειασμα δεδομένων του πίνακα `TENT_SPACE`
--

INSERT INTO `TENT_SPACE` (`suid`, `size`, `tid`) VALUES
(301, 5, 1),
(302, 5, 2),
(303, 5, 3),
(304, 5, 4),
(305, 5, 5),
(306, 5, 6),
(307, 5, 7),
(308, 5, 8),
(309, 5, 9),
(311, 5, 11),
(312, 5, 12),
(313, 5, 13),
(314, 5, 14),
(315, 5, 15),
(316, 5, 16),
(317, 5, 17),
(318, 5, 18),
(319, 5, 19),
(321, 5, 21),
(322, 5, 22),
(323, 5, 23),
(324, 5, 24),
(325, 5, 25),
(326, 5, 26),
(327, 5, 27),
(328, 5, 28),
(329, 5, 29);

--
-- Ευρετήρια για άχρηστους πίνακες
--

--
-- Ευρετήρια για πίνακα `ACCOMODATION_SPOT`
--
ALTER TABLE `ACCOMODATION_SPOT`
  ADD PRIMARY KEY (`suid`),
  ADD KEY `class_name` (`class_name`,`class_type`);

--
-- Ευρετήρια για πίνακα `BUNGALOW`
--
ALTER TABLE `BUNGALOW`
  ADD PRIMARY KEY (`suid`),
  ADD UNIQUE KEY `idx_buid` (`buid`);

--
-- Ευρετήρια για πίνακα `CONTAINED_CUSTOMER`
--
ALTER TABLE `CONTAINED_CUSTOMER`
  ADD PRIMARY KEY (`cuid`,`ruid`),
  ADD KEY `ruid` (`ruid`);

--
-- Ευρετήρια για πίνακα `CUSTOMER`
--
ALTER TABLE `CUSTOMER`
  ADD PRIMARY KEY (`cuid`);

--
-- Ευρετήρια για πίνακα `INCLUDED_SERVICE`
--
ALTER TABLE `INCLUDED_SERVICE`
  ADD PRIMARY KEY (`service_name`,`ruid`),
  ADD KEY `ruid` (`ruid`);

--
-- Ευρετήρια για πίνακα `PARKING_SPOT`
--
ALTER TABLE `PARKING_SPOT`
  ADD PRIMARY KEY (`letter`,`number`);

--
-- Ευρετήρια για πίνακα `PAYMENT`
--
ALTER TABLE `PAYMENT`
  ADD PRIMARY KEY (`puid`),
  ADD KEY `ruid` (`ruid`);

--
-- Ευρετήρια για πίνακα `RESERVATION`
--
ALTER TABLE `RESERVATION`
  ADD PRIMARY KEY (`ruid`),
  ADD KEY `main_cuid` (`main_cuid`);

--
-- Ευρετήρια για πίνακα `RESERVED_PARKING`
--
ALTER TABLE `RESERVED_PARKING`
  ADD PRIMARY KEY (`ruid`,`pletter`,`pnumber`),
  ADD KEY `pletter` (`pletter`,`pnumber`);

--
-- Ευρετήρια για πίνακα `RESERVED_SPOT`
--
ALTER TABLE `RESERVED_SPOT`
  ADD PRIMARY KEY (`ruid`,`suid`),
  ADD KEY `suid` (`suid`);

--
-- Ευρετήρια για πίνακα `RV_SPOT`
--
ALTER TABLE `RV_SPOT`
  ADD PRIMARY KEY (`suid`),
  ADD UNIQUE KEY `idx_rvid` (`rvid`);

--
-- Ευρετήρια για πίνακα `SERVICE`
--
ALTER TABLE `SERVICE`
  ADD PRIMARY KEY (`name`);

--
-- Ευρετήρια για πίνακα `SPOT_CLASS`
--
ALTER TABLE `SPOT_CLASS`
  ADD PRIMARY KEY (`class_name`,`class_type`,`season`);

--
-- Ευρετήρια για πίνακα `TENT_SPACE`
--
ALTER TABLE `TENT_SPACE`
  ADD PRIMARY KEY (`suid`),
  ADD UNIQUE KEY `idx_tid` (`tid`);

--
-- AUTO_INCREMENT για άχρηστους πίνακες
--

--
-- AUTO_INCREMENT για πίνακα `ACCOMODATION_SPOT`
--
ALTER TABLE `ACCOMODATION_SPOT`
  MODIFY `suid` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=330;

--
-- AUTO_INCREMENT για πίνακα `CUSTOMER`
--
ALTER TABLE `CUSTOMER`
  MODIFY `cuid` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=54;

--
-- AUTO_INCREMENT για πίνακα `PAYMENT`
--
ALTER TABLE `PAYMENT`
  MODIFY `puid` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT για πίνακα `RESERVATION`
--
ALTER TABLE `RESERVATION`
  MODIFY `ruid` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=425;

--
-- Περιορισμοί για άχρηστους πίνακες
--

--
-- Περιορισμοί για πίνακα `ACCOMODATION_SPOT`
--
ALTER TABLE `ACCOMODATION_SPOT`
  ADD CONSTRAINT `ACCOMODATION_SPOT_ibfk_1` FOREIGN KEY (`class_name`,`class_type`) REFERENCES `SPOT_CLASS` (`class_name`, `class_type`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Περιορισμοί για πίνακα `BUNGALOW`
--
ALTER TABLE `BUNGALOW`
  ADD CONSTRAINT `BUNGALOW_ibfk_1` FOREIGN KEY (`suid`) REFERENCES `ACCOMODATION_SPOT` (`suid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Περιορισμοί για πίνακα `CONTAINED_CUSTOMER`
--
ALTER TABLE `CONTAINED_CUSTOMER`
  ADD CONSTRAINT `CONTAINED_CUSTOMER_ibfk_1` FOREIGN KEY (`cuid`) REFERENCES `CUSTOMER` (`cuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `CONTAINED_CUSTOMER_ibfk_2` FOREIGN KEY (`ruid`) REFERENCES `RESERVATION` (`ruid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Περιορισμοί για πίνακα `INCLUDED_SERVICE`
--
ALTER TABLE `INCLUDED_SERVICE`
  ADD CONSTRAINT `INCLUDED_SERVICE_ibfk_1` FOREIGN KEY (`service_name`) REFERENCES `SERVICE` (`name`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `INCLUDED_SERVICE_ibfk_2` FOREIGN KEY (`ruid`) REFERENCES `RESERVATION` (`ruid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Περιορισμοί για πίνακα `PAYMENT`
--
ALTER TABLE `PAYMENT`
  ADD CONSTRAINT `PAYMENT_ibfk_1` FOREIGN KEY (`ruid`) REFERENCES `RESERVATION` (`ruid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Περιορισμοί για πίνακα `RESERVATION`
--
ALTER TABLE `RESERVATION`
  ADD CONSTRAINT `RESERVATION_ibfk_1` FOREIGN KEY (`main_cuid`) REFERENCES `CUSTOMER` (`cuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Περιορισμοί για πίνακα `RESERVED_PARKING`
--
ALTER TABLE `RESERVED_PARKING`
  ADD CONSTRAINT `fk_parking_pletter_pnumber` FOREIGN KEY (`pletter`,`pnumber`) REFERENCES `PARKING_SPOT` (`letter`, `number`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  ADD CONSTRAINT `fk_reservation_ruid` FOREIGN KEY (`ruid`) REFERENCES `RESERVATION` (`ruid`);

--
-- Περιορισμοί για πίνακα `RESERVED_SPOT`
--
ALTER TABLE `RESERVED_SPOT`
  ADD CONSTRAINT `RESERVED_SPOT_ibfk_ruid` FOREIGN KEY (`ruid`) REFERENCES `RESERVATION` (`ruid`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `RESERVED_SPOT_ibfk_suid` FOREIGN KEY (`suid`) REFERENCES `ACCOMODATION_SPOT` (`suid`) ON DELETE RESTRICT ON UPDATE RESTRICT;

--
-- Περιορισμοί για πίνακα `RV_SPOT`
--
ALTER TABLE `RV_SPOT`
  ADD CONSTRAINT `RV_SPOT_ibfk_1` FOREIGN KEY (`suid`) REFERENCES `ACCOMODATION_SPOT` (`suid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Περιορισμοί για πίνακα `TENT_SPACE`
--
ALTER TABLE `TENT_SPACE`
  ADD CONSTRAINT `TENT_SPACE_ibfk_1` FOREIGN KEY (`suid`) REFERENCES `ACCOMODATION_SPOT` (`suid`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
