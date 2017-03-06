program delphitest;

uses
  Forms,
  dtmain in 'dtmain.pas' {Form1},
  phpgd2 in 'phpgd2.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
