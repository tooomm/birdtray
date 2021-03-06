#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QProgressDialog>
#include <QPalette>
#include <QtCore/QStringListModel>

#include "databaseaccounts.h"
#include "ui_dialogsettings.h"

#ifdef Q_OS_WIN
#  define THUNDERBIRD_PROFILES_PATH "%AppData%\\Thunderbird\\Profiles"
#else
#  define THUNDERBIRD_PROFILES_PATH "~/Library/Thunderbird/Profiles"
#endif


class ModelAccountTree;
class ModelNewEmails;

class DialogSettings : public QDialog, public Ui::DialogSettings
{
    Q_OBJECT

    public:
        explicit DialogSettings(QWidget *parent = 0);

    public slots:
        void    accept() override;
        void    browsePath();
        void    profilePathChanged();
        
        /**
         * Called once the update check finished.
         *
         * @param hasUpdate true if a new update was found.
         * @param errorMessage A message indicating an error during the check, or a null string.
         */
        void    onCheckUpdateFinished(bool foundUpdate, const QString &errorString);

        // Calls the database fixer running in a DatabaseFixer thread
        // Receives databaseUnreadsFixed() once fixed
        void    fixDatabaseUnreads();
        void    databaseUnreadsUpdate( int progresspercentage );
        void    databaseUnreadsFixed(QString errorMsg);

        // Tab activation (to refresh accounts)
        // Calls the account query running in a DatabaseAccounts thread
        void    activateTab(int tabIndex );

        // Receives accountsAvailable()
        void    accountsAvailable(QString errorMsg);

        // Account buttons
        /**
         * Add one or multiple accounts.
         */
        void    accountAdd();
        void    accountEdit();
        void    accountEditIndex( const QModelIndex& index );
        void    accountRemove();

        // New Email buttons
        void    newEmailAdd();
        void    newEmailEdit();
        void    newEmailEditIndex( const QModelIndex& index );
        void    newEmailRemove();
        
        // Advanced buttons
        void    onCheckUpdateButton();
        void    onShowLogWindow();

        // Icon change
        void    buttonChangeIcon();
        void    buttonChangeUnreadIcon();
        
        /**
         * The unread count border width changed.
         * @param value The new border width.
         */
        void onBorderWidthChanged(int value);

        // Parser changed
        void    unreadParserChanged( int curr );

    private:
        void    changeIcon(QToolButton * button );
        
        /**
         * Update the account list from the selected sql database.
         */
        void    updateAccountList();
        
        /**
         * Validate the profile path.
         *
         * @param profilePath The profile path.
         * @return true, if the path is valid, false otherwise.
         */
        bool    isProfilePathValid(const QString& profilePath) const;
        
        /**
         * Check if the given profile path is valid and display a dialog, if it's not.
         *
         * @param profilePath The profile path.
         * @return true, if the path is valid, false otherwise.
         */
        bool    reportIfProfilePathValid(const QString& profilePath) const;
        bool    isMorkParserSelected() const;
    
        QPalette mPaletteOk;
        QPalette mPaletteError;

        // For database fixer
        QProgressDialog * mProgressFixer;

        // List of all accounts
        QList<DatabaseAccounts::Account>    mAccounts;

        // Model to show the accounts
        ModelAccountTree    *   mAccountModel;

        // Model to show new emails
        ModelNewEmails      *   mModelNewEmails;
};

#endif // SETTINGSDIALOG_H
