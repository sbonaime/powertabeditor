/*
  * Copyright (C) 2011 Cameron White
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
  
#ifndef KEYSIGNATUREDIALOG_H
#define KEYSIGNATUREDIALOG_H

#include <QDialog>
#include <powertabdocument/keysignature.h>

namespace Ui {
    class KeySignatureDialog;
}

class KeySignatureDialog : public QDialog
{
    Q_OBJECT
public:
    KeySignatureDialog(QWidget* parent, const KeySignature& key);
    ~KeySignatureDialog();

    KeySignature getNewKey() const;

private slots:
    void accept();
    void populateKeyTypes(uint8_t type);
    void handleModification();

private:
    Ui::KeySignatureDialog *ui;

    KeySignature newKey;
    bool modified;
};

#endif // KEYSIGNATUREDIALOG_H
