#include "stdafx.h"

using namespace System;

void listo(String^ dir);
void listf(String^dir);
void hilfe(void);

int main(array<System::String ^> ^args)
{
	String^ curDir = IO::Directory::GetCurrentDirectory();
	Console::WriteLine(curDir);
	String^ command = "";
	array<String^>^ argus;
	while (true) {
		Console::Write(">>># ");
		command = Console::ReadLine();
		argus = command->Split(' ');
		if (command == "abbruch") break;
		else if (command == "auf") {
			curDir = IO::Directory::GetParent(curDir)->ToString();
			Console::WriteLine(curDir);
		}
		else if (command == "wo") { Console::WriteLine(curDir); }
		else if (argus[0] == "gehe") {
			try
			{
				curDir += "\\" + argus[1];
				IO::Directory::SetCurrentDirectory(curDir);
				Console::WriteLine(curDir);
			}
			catch (Exception^e) { Console::WriteLine(e->Message); }
		}
		else if (command == "listf") { listf(curDir); }
		else if (command == "listo") { listo(curDir); }
		else if (command == "list") {
			listf(curDir);
			listo(curDir);
		}
		else if (argus[0] == "neuO") {
			try { IO::Directory::CreateDirectory(curDir + "\\" + argus[1]); }
			catch (Exception^ e) { Console::WriteLine(e->Message); }
		}
		else if (argus[0] == "neuD") {
			try { IO::File::Create(curDir + "\\" + argus[1] + ".txt"); }
			catch (Exception^e) { Console::WriteLine(e->Message); }
		}
		else if (argus[0] == "zeige") {
			try
			{
				array<String^> ^inhalt = IO::File::ReadAllLines(curDir + "\\" + argus[1]);
				for each (String^ str in inhalt) { Console::WriteLine(str); }
			}
			catch (Exception^e) { Console::WriteLine(e->Message); }
		}
		else if (argus[0] == "kopiere") {
			bool sure = true;
			if (IO::File::Exists(curDir + "\\" + argus[2])) {
				Console::WriteLine("Bist du sicher?");
				sure = Console::ReadLine()[0] == 'j';
			}
			if (sure) {
				try { IO::File::Copy(curDir + "\\" + argus[1], curDir + "\\" + argus[2]); }
				catch (Exception^e) { Console::WriteLine(e->Message); }
			}
		}
		else if (argus[0] == "loesche") {
			try { IO::File::Delete(curDir + "\\" + argus[1]); }
			catch (Exception^e) { Console::WriteLine(e->Message); }
		}
		else if (argus[0] == "datum") {
			try {
				Console::WriteLine(argus[1] + ": "
					+ IO::File::GetCreationTime(curDir + "\\" + argus[1]));
			}
			catch (Exception^e) { Console::WriteLine(e->Message); }
		}
		else if (argus[0] == "verschiebe") {
			try { IO::File::Move(curDir + "\\" + argus[1], argus[2]); }
			catch (Exception^e) { Console::WriteLine(e->Message); }
		}
		else if (argus[0] == "groesse") {
			unsigned long bytes;
			try { bytes = IO::File::ReadAllBytes(curDir + "\\" + argus[1])->Length; }
			catch (Exception^ e) { Console::WriteLine(e->Message); }
			try {
				switch (argus[2]->ToLower()[0]) {
				case 'k': Console::WriteLine((bytes / (double)1024).ToString("F2") + " Kibibytes"); break;
				case 'm': Console::WriteLine((bytes / (double)(1024 * 1024)).ToString("F2")
					+ " Mebibytes"); break;
				case 'g': Console::WriteLine((bytes / (double)(1024 * 1024 * 1024)).ToString("F2")
					+ " Gibibytes"); break;
				default: {}
				}
			}
			catch (Exception^) { Console::WriteLine(bytes + " Bytes"); }
		}
		else if (command == "hilfe") { hilfe(); }
		else { Console::WriteLine("Dieser Befehl ist mir nicht bekannt. 'hilfe' fuer Hilfe."); }
	}
	return 0;
}

void listo(String ^ dir)
{
	array<String^>^arrDirs = IO::Directory::GetDirectories(dir);
	for each(String^ str in arrDirs) { Console::WriteLine(str); }
}

void listf(String ^ dir)
{
	array<String^>^ arrFiles = IO::Directory::GetFiles(dir);
	for each(String^ str in arrFiles) { Console::WriteLine(str); }
}

void hilfe(void)
{
	array<String^>^ text = {
		"abbruch - Abbruch",
		"auf - Ordner hoeher",
		"wo - Zeigt das aktuelle Verzeichnis",
		"gehe [Verzeichnis] - Wechselt in das relative Verzeichnis",
		"listf - Listet Dateien",
		"listo - Listet Ordner",
		"list - Listet alles",
		"neuO [Name] - Neuer Ordner",
		"neuD [name] - Neue Textdatei",
		"zeige [name] - Zeigt Inhalt",
		"kopiere [datei1] [datei2] - Kopiert Dateien",
		"loesche [datei] - Loescht Datei",
		"datum [datei] - Zeigt Erstelldatum",
		"verschiebe [datei] [Zielort] - Verschiebt datei",
		"groesse [datei] [opt. k|m|g] - Gibt die Groesse in Bytes an"
	};
	for each (String^ str in text) { Console::WriteLine(str); }
}
