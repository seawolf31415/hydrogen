/*
 * Hydrogen
 * Copyright(c) 2002-2008 by Alex >Comix< Cominu [comix@users.sourceforge.net]
 * Copyright(c) 2008-2021 The hydrogen development team [hydrogen-devel@lists.sourceforge.net]
 *
 * http://www.hydrogen-music.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses
 *
 */

#ifndef CLICKABLE_LABEL_H
#define CLICKABLE_LABEL_H

#include <core/Object.h>
#include <core/Preferences.h>

#include <QtGui>
#include <QtWidgets>

/** Custom QLabel that emits a signal when clicked.
 *
 * The label tries to be smart when choosing the font size. It knows
 * its own size and decreases the font size - if the original would
 * make the text overflow - until the text fits.
 *
 */
class ClickableLabel : public QLabel, public H2Core::Object
{
	H2_OBJECT
	Q_OBJECT

public:
	/** The individual colors of the text won't be exposed but are up
		to the palette/application-wide settings.*/
	enum class Color {
		Bright,
		Dark
	};
	
	explicit ClickableLabel( QWidget *pParent, QSize size = QSize( 0, 0 ), QString sText = "", Color color = Color::Bright );
	void mousePressEvent( QMouseEvent * e );

public slots:
	void onPreferencesChanged( bool bAppearanceOnly );
	void setText( const QString& sNewText );

signals:
	void labelClicked( ClickableLabel* pLabel );

private:
	void updateStyleSheet();
	void updateFont( QString sFontFamily, H2Core::Preferences::FontSize fontSize );

	QSize m_size;
	Color m_color;
	
	QColor m_lastWindowColor;
	QColor m_lastWindowTextColor;
	QColor m_lastWidgetColor;
	QColor m_lastWidgetTextColor;
	/** Used to detect changed in the font*/
	QString m_sLastUsedFontFamily;
	/** Used to detect changed in the font*/
	H2Core::Preferences::FontSize m_lastUsedFontSize;
};


#endif

