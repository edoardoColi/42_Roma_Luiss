<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the installation.
 * You don't have to use the web site, you can copy this file to "wp-config.php"
 * and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * Database settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/documentation/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** Database settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'mariArchive' );

/** Database username */
define( 'DB_USER', 'ecoli' );

/** Database password */
define( 'DB_PASSWORD', '53cur3PwD2' );

/** Database hostname */
define( 'DB_HOST', 'mariadb' );

/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8mb4' );

/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Change these to different unique phrases! You can generate these using
 * the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}.
 *
 * You can change these at any point in time to invalidate all existing cookies.
 * This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define( 'AUTH_KEY',         'BcQ}2^0mU{kGghP<hi&{IY8{@S<*O`G!5B5|%[1>C{X+odJ`9bPMGA@!d+xcVqxm' );
define( 'SECURE_AUTH_KEY',  'QWFw{*6gtLIoXv7LFrD4ZWwkf=h:3ZMk  3/8(xPFqf.OT0#OJ2fE)<{}~Fy~5QA' );
define( 'LOGGED_IN_KEY',    '<tfCgO0#L5a{@%QM)afh,`#B;RsRwKt%L<>R 8zub?-QsH<U&:?ZET+#Dd$4O-H4' );
define( 'NONCE_KEY',        'v.fvGFpRnCdsabDNnh}FVh8~55<eTrv=Mc3Y%Y S<Yb^+M&Zp(@yCJRu4R PK+AS' );
define( 'AUTH_SALT',        'tj***K{3f-34el+qKE$aSeT=ZPZ1od|3PxrCt/3w1p**vi}`<8nxJ56ZO)zoiQ_j' );
define( 'SECURE_AUTH_SALT', ').*5fQ/)e@.aSstp}fih$vZ=GC7f9R`;FO|(=NoGCro&EC,Cj;.fm,k8LC(9ACXZ' );
define( 'LOGGED_IN_SALT',   'Qsi.o3),DtBM{HIn]Yu(7*lo(`^Gt(;Bm~M,!?w#]M+Udfr^w9XS*&J0 uwcbM#J' );
define( 'NONCE_SALT',       '| |$[rh>[=[ouLxF3X+Kmih>XaHsG|?C~7X}#V9AVK=yu+i^~h;!3 JoiO]Kg~1j' );

/**#@-*/

/**
 * WordPress database table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/documentation/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* Add any custom values between this line and the "stop editing" line. */



/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
