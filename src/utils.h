#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QtCore/QFileInfo>

class Utils
{
    public:
        // Decodes IMAP UTF7 data
        static QString  decodeIMAPutf7( const QString& param );
    
        /**
         * Expand the path as a shell would do. This will expand variables and ~/.
         * This function will also remove wrapping quotes.
         *
         * @param path The path.
         * @return The expanded path.
         */
        static QString expandPath(const QString& path);
        
        /**
         * @return The version of Birdtray as a string.
         */
        static QString getBirdtrayVersion();
        
        /**
         * @return The name of the Thunderbird updater executable.
         */
        static QString getThunderbirdUpdaterName();

        /**
         * Convert a std::wstring to a QString.
         *
         * @param str The std:wstring.
         * @return The QString with the contents of the original string.
         */
        static QString stdWToQString(const std::wstring &str);

        /**
         * Convert a QString to a std::wstring.
         *
         * @param str The QString.
         * @return The std::wstring with the contents of the original string.
         */
        static std::wstring qToStdWString(const QString &str);

        /**
         * @return A list of possible locations of the directory
         *         that contains the Thunderbird profiles.
         * @see https://support.mozilla.org/en-US/kb/profiles-where-thunderbird-stores-user-data#w_profile-location-summary
         */
        static QStringList getThunderbirdProfilesPaths();

        /**
         * @return The default Thunderbird command for the current platform.
         */
        static QStringList getDefaultThunderbirdCommand();

        // Splits the string into stringlist using space as separator, but ignoring spaces inside quoted content
        static QStringList splitCommandLine( const QString& src );
        
        /**
         * Get the mail folder name from the mork path.
         *
         * @param morkPath The file info for a msf file.
         * @return The mail folder name.
         */
        static QString getMailFolderName(const QFileInfo &morkFile);
        
        /**
         * Get the mil account name from a mork path
         *
         * @param morkPath The file info for a msf file.
         * @return The mail account name.
         */
        static QString getMailAccountName(const QFileInfo &morkFile);
};

#endif // UTILS_H
