/*****************************************************************************
 * LibreMines                                                                *
 * Copyright (C) 2020  Bruno Bollos Correa                                   *
 *                                                                           *
 * This program is free software: you can redistribute it and/or modify      *
 * it under the terms of the GNU General Public License as published by      *
 * the Free Software Foundation, either version 3 of the License, or         *
 * (at your option) any later version.                                       *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.     *
 *****************************************************************************
 */


#ifndef LIBREMINESGUI_H
#define LIBREMINESGUI_H

#include <QDesktopWidget>
#include <QSpinBox>
#include <QTimer>
#include <QLCDNumber>
#include <QCheckBox>
#include <QMainWindow>

#include "common.h"
#include "libreminesgameengine.h"
#include "qlabel_adapted.h"
#include "qpushbutton_adapted.h"


/**
 * @brief
 *
 */
class LibreMinesGui : public QMainWindow
{
    Q_OBJECT

private:
    class CellGui
    {
    public:
        CellGui();

        QPushButton_adapted *button; /**< TODO: describe */
        QLabel_adapted *label; /**< TODO: describe */
    };

public:
    /**
     * @brief
     *
     * @param parent
     */
    LibreMinesGui(QWidget *parent = nullptr, const int thatWidth = -1, const int thatHeight = -1, const int thatMaximumCellLength = 999999999);
    /**
     * @brief
     *
     */
    ~LibreMinesGui();

    /**
     * @brief
     *
     * @param _X
     * @param _Y
     * @param i_nMines_
     * @param i_X_Clean
     * @param i_Y_Clean
     */

protected:
    bool eventFilter(QObject* object, QEvent* event);

private:
    void vNewGame(const uchar _X,
                  const uchar _Y,
                  ushort i_nMines_);

    void vAttributeAllCells();
    void vResetPrincipalMatrix();
    /**
     * @brief
     *
     */
    void vConfigureInterface(int width, int height);
    /**
     * @brief
     *
     */
    void vHideInterface();
    /**
     * @brief
     *
     */
    void vShowInterface();
    /**
     * @brief
     *
     */
    void vAjustInterfaceInGame();
    /**
     * @brief
     *
     */
    void vHideInterfaceInGame();
    /**
     * @brief
     *
     */
    void vShowInterfaceInGame();

    void vConfigureTheme(const bool bDark);

    void vKeyboardControllerSetCurrentCell(const uchar x, const uchar y);
    void vKeyboardControllUnsetCurrentCell();
    void vKeyboardControllerMoveLeft();
    void vKeyboardControllerMoveRight();
    void vKeyboardControllerMoveDown();
    void vKeyboardControllerMoveUp();

    void vLastSessionLoadConfigurationFile();
    void vLastSessionSaveConfigurationFile();

private Q_SLOTS:
    /**
     * @brief
     *
     */
    void SLOT_Easy();
    /**
     * @brief
     *
     */
    void SLOT_Medium();
    /**
     * @brief
     *
     */
    void SLOT_Hard();
    /**
     * @brief
     *
     */
    void SLOT_Customized();

    /**
     * @brief
     *
     */
    void SLOT_Quit();
    /**
     * @brief
     *
     */
    void SLOT_Restart();

    ///
    /// \brief SLOT_DarkMode
    ///
    void SLOT_DarkMode();

    /**
     * @brief
     *
     * @param e
     */
    void SLOT_OnCellButtonClicked(const QMouseEvent *const e);

    void SLOT_onCellLabelClicked(const QMouseEvent *const e);

    void SLOT_showCell(const uchar _X, const uchar _Y);
    void SLOT_endGameScore(LibreMinesScore score,
                           int iCorrectFlags,
                           int iWrongFlags,
                           int iUnlockedCells,
                           double dFlagsPerSecond,
                           double dCellsPerSecond);
    void SLOT_currentTime(const ushort time);
    void SLOT_minesLeft(const ushort minesLeft);
    void SLOT_flagCell(const uchar _X, const uchar _Y);
    void SLOT_unflagCell(const uchar _X, const uchar _Y);

    void SLOT_remakeGame();
    void SLOT_gameWon();
    void SLOT_gameLost(const uchar _X, const uchar _Y);

Q_SIGNALS:
    void SIGNAL_cleanCell(const uchar _X, const uchar _Y);
    void SIGNAL_cleanNeighborCells(const uchar _X, const uchar _Y);
    void SIGNAL_addOrRemoveFlag(const uchar _X, const uchar _Y);
    void SIGNAL_stopGame();

private:

    QScopedPointer<LibreMinesGameEngine> gameEngine;
    std::vector< std::vector<CellGui> > principalMatrix; /**< TODO: describe */

    int iLimitHeightField; /**< TODO: describe */
    int iLimitWidthField; /**< TODO: describe */

    int iWidthMainWindow;
    int iHeightMainWindow;

    int cellLength; /**< TODO: describe */
    const int maximumCellLength;

    GAME_DIFFICULTY difficult; /**< TODO: describe */

    QPushButton *buttonEasy; /**< TODO: describe */
    QPushButton *buttonMedium; /**< TODO: describe */
    QPushButton *buttonHard; /**< TODO: describe */

    QPushButton *buttonCustomizedNewGame; /**< TODO: describe */

    QSpinBox *sbCustomizedX; /**< TODO: describe */
    QSpinBox *sbCustomizedY; /**< TODO: describe */
    QSpinBox *sbCustomizednMines; /**< TODO: describe */

    QLabel *labelCustomizedX; /**< TODO: describe */
    QLabel *labelCustomizedY; /**< TODO: describe */
    QLabel *labelCustomized_nMines; /**< TODO: describe */

    QCheckBox *cbFirstCellClean; /**< TODO: describe */
    QCheckBox *cbDarkModeEnabled;
    QCheckBox* cbCleanNeighborCellsWhenClickedOnShowedCell;

    QLabel* labelUsername;
    QLineEdit* lineEditUsername;

    QLabel *labelTimerInGame; /**< TODO: describe */
    QLCDNumber *lcd_numberMinesLeft; /**< TODO: describe */
    QPushButton *buttonRestartInGame; /**< TODO: describe */
    QPushButton *buttonQuitInGame; /**< TODO: describe */

    QLabel *labelYouWonYouLost; /**< TODO: describe */
    QLabel *labelStatisLastMatch; /**< TODO: describe */

    QImage *imgZero; /**< TODO: describe */
    QImage *imgOne; /**< TODO: describe */
    QImage *imgTwo; /**< TODO: describe */
    QImage *imgThree; /**< TODO: describe */
    QImage *imgFour; /**< TODO: describe */
    QImage *imgFive; /**< TODO: describe */
    QImage *imgSix; /**< TODO: describe */
    QImage *imgSeven; /**< TODO: describe */
    QImage *imgEight; /**< TODO: describe */
    QImage *imgFlag; /**< TODO: describe */
    QImage *imgNoFlag; /**< TODO: describe */
    QImage *imgMine; /**< TODO: describe */
    QImage *imgBoom; /**< TODO: describe */
    QImage *imgWrongFlag; /**< TODO: describe */

    KeyboardController controller;
};
#endif // LIBREMINESGUI_H
