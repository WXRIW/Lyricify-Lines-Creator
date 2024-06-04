/************************************************************************
 * Filename:    InternationalizationHelper.cpp
 * Description: 本地化方法实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/Lyricify-Lines-Creator
 * License:     LGPL-2.1 license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "InternationalizationHelper.h"

std::map<std::string, std::map<Languages, std::wstring>> translations =
{
	{
		"String.Window.Main.SelectAudio",
		{
			{ Languages::EN, L"Select Audio:" },
			{ Languages::ZH_HANS, L"选择音频：" },
			{ Languages::ZH_HANT, L"選擇音頻：" },
			{ Languages::FR, L"Sélectionner l'audio :" },
			{ Languages::RU, L"Выберите аудио:" }
		}
	},
	{
		"String.Window.Main.SelectLyrics",
		{
			{ Languages::EN, L"Select Lyrics:" },
			{ Languages::ZH_HANS, L"选择歌词：" },
			{ Languages::ZH_HANT, L"選擇歌詞：" },
			{ Languages::FR, L"Sélectionner les paroles :" },
			{ Languages::RU, L"Выберите текст песни:" }
		}
	},
	{
		"String.Window.Main.OutputPath",
		{
			{ Languages::EN, L"Output Path:" },
			{ Languages::ZH_HANS, L"输出路径：" },
			{ Languages::ZH_HANT, L"輸出路徑：" },
			{ Languages::FR, L"Chemin de sortie :" },
			{ Languages::RU, L"Путь вывода:" }
		}
	},
	{
		"String.Window.Main.ImportAudio",
		{
			{ Languages::EN, L"Import Audio" },
			{ Languages::ZH_HANS, L"导入音频" },
			{ Languages::ZH_HANT, L"導入音頻" },
			{ Languages::FR, L"Importer l'audio" },
			{ Languages::RU, L"Импорт аудио" }
		}
	},
	{
		"String.Window.Main.ImportLyrics",
		{
			{ Languages::EN, L"Import Lyrics" },
			{ Languages::ZH_HANS, L"导入歌词" },
			{ Languages::ZH_HANT, L"導入歌詞" },
			{ Languages::FR, L"Importer les paroles" },
			{ Languages::RU, L"Импорт текста песни" }
		}
	},
	{
		"String.Window.Main.SelectPath",
		{
			{ Languages::EN, L"Select Path" },
			{ Languages::ZH_HANS, L"选择路径" },
			{ Languages::ZH_HANT, L"選擇路徑" },
			{ Languages::FR, L"Sélectionner le chemin" },
			{ Languages::RU, L"Выберите путь" }
		}
	},
	{
		"String.Window.Main.Play",
		{
			{ Languages::EN, L"Play" },
			{ Languages::ZH_HANS, L"播放" },
			{ Languages::ZH_HANT, L"播放" },
			{ Languages::FR, L"Jouer" },
			{ Languages::RU, L"Играть" }
		}
	},
	{
		"String.Window.Main.Pause",
		{
			{ Languages::EN, L"Pause" },
			{ Languages::ZH_HANS, L"暂停" },
			{ Languages::ZH_HANT, L"暫停" },
			{ Languages::FR, L"Pause" },
			{ Languages::RU, L"Пауза" }
		}
	},
	{
		"String.Window.Main.About",
		{
			{ Languages::EN, L"About" },
			{ Languages::ZH_HANS, L"关于" },
			{ Languages::ZH_HANT, L"關於" },
			{ Languages::FR, L"À propos" },
			{ Languages::RU, L"О программе" }
		}
	},
	{
		"String.Window.Main.Settings",
		{
			{ Languages::EN, L"Settings" },
			{ Languages::ZH_HANS, L"设置" },
			{ Languages::ZH_HANT, L"設置" },
			{ Languages::FR, L"Paramètres" },
			{ Languages::RU, L"Настройки" }
		}
	},
	{
		"String.Window.Main.ViewOutput",
		{
			{ Languages::EN, L"View Output" },
			{ Languages::ZH_HANS, L"查看输出" },
			{ Languages::ZH_HANT, L"查看輸出" },
			{ Languages::FR, L"Voir la sortie" },
			{ Languages::RU, L"Просмотр вывода" }
		}
	},
	{
		"String.Window.Main.Preview",
		{
			{ Languages::EN, L"Preview" },
			{ Languages::ZH_HANS, L"预览效果" },
			{ Languages::ZH_HANT, L"預覽效果" },
			{ Languages::FR, L"Aperçu" },
			{ Languages::RU, L"Предварительный просмотр" }
		}
	},
	{
		"String.Window.Main.Restart",
		{
			{ Languages::EN, L"Restart" },
			{ Languages::ZH_HANS, L"重新制作" },
			{ Languages::ZH_HANT, L"重新製作" },
			{ Languages::FR, L"Redémarrer" },
			{ Languages::RU, L"Перезапуск" }
		}
	},
	{
		"String.Window.Main.Start",
		{
			{ Languages::EN, L"Start" },
			{ Languages::ZH_HANS, L"开始制作" },
			{ Languages::ZH_HANT, L"開始製作" },
			{ Languages::FR, L"Commencer" },
			{ Languages::RU, L"Начать" }
		}
	},
	{
		"String.Window.Main.SaveLyrics",
		{
			{ Languages::EN, L"Save Lyrics" },
			{ Languages::ZH_HANS, L"保存歌词" },
			{ Languages::ZH_HANT, L"保存歌詞" },
			{ Languages::FR, L"Enregistrer les paroles" },
			{ Languages::RU, L"Сохранить текст песни" }
		}
	},
	{
		"String.Window.Main.AudioLoadFailed",
		{
			{ Languages::EN, L"Audio load failed!" },
			{ Languages::ZH_HANS, L"音频加载失败！" },
			{ Languages::ZH_HANT, L"音頻加載失敗！" },
			{ Languages::FR, L"Échec du chargement de l'audio !" },
			{ Languages::RU, L"Не удалось загрузить аудио!" }
		}
	},
	{
		"String.Window.Main.SelectAudioDialogTitle",
		{
			{ Languages::EN, L"Select Audio" },
			{ Languages::ZH_HANS, L"选择音频" },
			{ Languages::ZH_HANT, L"選擇音頻" },
			{ Languages::FR, L"Sélectionner l'audio" },
			{ Languages::RU, L"Выберите аудио" }
		}
	},
	{
		"String.Window.Main.SelectAudioDialogFilter",
		{
			{ Languages::EN, L"Audio (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" },
			{ Languages::ZH_HANS, L"音频 (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" },
			{ Languages::ZH_HANT, L"音頻 (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" },
			{ Languages::FR, L"Audio (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" },
			{ Languages::RU, L"Аудио (*.mp3;*.wav;*.flac;*.ogg)\0*.mp3;*.wav;*.flac;*.ogg" }
		}
	},
	{
		"String.Window.Main.SelectLyricsDialogTitle",
		{
			{ Languages::EN, L"Select Lyrics" },
			{ Languages::ZH_HANS, L"选择歌词" },
			{ Languages::ZH_HANT, L"選擇歌詞" },
			{ Languages::FR, L"Sélectionner les paroles" },
			{ Languages::RU, L"Выберите текст песни" }
		}
	},
	{
		"String.Window.Main.SelectLyricsDialogFilter",
		{
			{ Languages::EN, L"Text Files (*.txt)\0*.txt" },
			{ Languages::ZH_HANS, L"文本文档 (*.txt)\0*.txt" },
			{ Languages::ZH_HANT, L"文本文件 (*.txt)\0*.txt" },
			{ Languages::FR, L"Fichiers texte (*.txt)\0*.txt" },
			{ Languages::RU, L"Текстовые файлы (*.txt)\0*.txt" }
		}
	},
	{
		"String.Window.Main.EmptyOrErrorText",
		{
			{ Languages::EN, L"The text is empty or an error occurred while reading!" },
			{ Languages::ZH_HANS, L"文本为空，或出现读取错误！" },
			{ Languages::ZH_HANT, L"文本為空，或出現讀取錯誤！" },
			{ Languages::FR, L"Le texte est vide ou une erreur est survenue lors de la lecture !" },
			{ Languages::RU, L"Текст пуст или произошла ошибка при чтении!" }
		}
	},
	{
		"String.Window.Main.OutputPathDialogTitle",
		{
			{ Languages::EN, L"Select Export Path" },
			{ Languages::ZH_HANS, L"选择导出路径" },
			{ Languages::ZH_HANT, L"選擇導出路徑" },
			{ Languages::FR, L"Sélectionner le chemin d'exportation" },
			{ Languages::RU, L"Выберите путь экспорта" }
		}
	},
	{
		"String.Window.Main.NoOutputToView",
		{
			{ Languages::EN, L"No output to view!" },
			{ Languages::ZH_HANS, L"没有可查看的输出！" },
			{ Languages::ZH_HANT, L"沒有可查看的輸出！" },
			{ Languages::FR, L"Aucune sortie à afficher !" },
			{ Languages::RU, L"Нет вывода для просмотра!" }
		}
	},
	{
		"String.Window.Main.NoPreviewToView",
		{
			{ Languages::EN, L"No preview to view!" },
			{ Languages::ZH_HANS, L"没有可查看的预览！" },
			{ Languages::ZH_HANT, L"沒有可查看的預覽！" },
			{ Languages::FR, L"Aucun aperçu à afficher !" },
			{ Languages::RU, L"Нет предварительного просмотра!" }
		}
	},
	{
		"String.Window.Main.NoAudioSelected",
		{
			{ Languages::EN, L"No audio selected!" },
			{ Languages::ZH_HANS, L"未选择音频！" },
			{ Languages::ZH_HANT, L"未選擇音頻！" },
			{ Languages::FR, L"Aucun audio sélectionné !" },
			{ Languages::RU, L"Аудио не выбрано!" }
		}
	},
	{
		"String.Window.Main.NoLyricsSelected",
		{
			{ Languages::EN, L"No lyrics file selected!" },
			{ Languages::ZH_HANS, L"未选择歌词文本！" },
			{ Languages::ZH_HANT, L"未選擇歌詞文件！" },
			{ Languages::FR, L"Aucun fichier de paroles sélectionné !" },
			{ Languages::RU, L"Файл с текстом песни не выбран!" }
		}
	},
	{
		"String.Window.Main.NoLyricsToSave",
		{
			{ Languages::EN, L"Save failed, no lyrics written to file!" },
			{ Languages::ZH_HANS, L"保存失败，没有歌词被写入文件！" },
			{ Languages::ZH_HANT, L"保存失敗，沒有歌詞被寫入文件！" },
			{ Languages::FR, L"Échec de l'enregistrement, aucune parole écrite dans le fichier !" },
			{ Languages::RU, L"Не удалось сохранить, текст песни не записан в файл!" }
		}
	},
	{
		"String.Window.Main.SaveFailed",
		{
			{ Languages::EN, L"Save failed, unable to write to file!" },
			{ Languages::ZH_HANS, L"保存失败，无法写入文件！" },
			{ Languages::ZH_HANT, L"保存失敗，無法寫入文件！" },
			{ Languages::FR, L"Échec de l'enregistrement, impossible d'écrire dans le fichier !" },
			{ Languages::RU, L"Не удалось сохранить, невозможно записать в файл!" }
		}
	},
	{
		"String.Window.Main.SaveFailedTitle",
		{
			{ Languages::EN, L"Save Failed" },
			{ Languages::ZH_HANS, L"保存失败" },
			{ Languages::ZH_HANT, L"保存失敗" },
			{ Languages::FR, L"Échec de l'enregistrement" },
			{ Languages::RU, L"Не удалось сохранить" }
		}
	},
	{
		"String.Window.Main.OutputSaveFailed",
		{
			{ Languages::EN, L"Save failed, unable to write to file!" },
			{ Languages::ZH_HANS, L"保存失败，无法写入文件！" },
			{ Languages::ZH_HANT, L"保存失敗，無法寫入文件！" },
			{ Languages::FR, L"Échec de l'enregistrement, impossible d'écrire dans le fichier !" },
			{ Languages::RU, L"Не удалось сохранить, невозможно записать в файл!" }
		}
	},
	{
		"String.Window.Main.OutputSaveSuccess",
		{
			{ Languages::EN, L"Save successful!" },
			{ Languages::ZH_HANS, L"保存成功！" },
			{ Languages::ZH_HANT, L"保存成功！" },
			{ Languages::FR, L"Enregistré avec succès !" },
			{ Languages::RU, L"Успешно сохранено!" }
		}
	},
	{
		"String.Window.Main.OutputSaveSuccessTitle",
		{
			{ Languages::EN, L"Save Successful" },
			{ Languages::ZH_HANS, L"保存成功" },
			{ Languages::ZH_HANT, L"保存成功" },
			{ Languages::FR, L"Enregistrement réussi" },
			{ Languages::RU, L"Успешное сохранение" }
		}
	},
	{
		"String.Window.Main.PreviousLine",
		{
			{ Languages::EN, L"Prev. Line:" },
			{ Languages::ZH_HANS, L"上一行：" },
			{ Languages::ZH_HANT, L"上一行：" },
			{ Languages::FR, L"Ligne précédente :" },
			{ Languages::RU, L"Предыдущая строка:" }
		}
	},
	{
		"String.Window.Main.CurrentLine",
		{
			{ Languages::EN, L"Curr. Line:" },
			{ Languages::ZH_HANS, L"当前行：" },
			{ Languages::ZH_HANT, L"當前行：" },
			{ Languages::FR, L"Ligne actuelle :" },
			{ Languages::RU, L"Текущая строка:" }
		}
	},
	{
		"String.Window.Main.NextLine",
		{
			{ Languages::EN, L"Next Line:" },
			{ Languages::ZH_HANS, L"下一行：" },
			{ Languages::ZH_HANT, L"下一行：" },
			{ Languages::FR, L"Ligne suivante :" },
			{ Languages::RU, L"Следующая строка:" }
		}
	},
	{
		"String.Window.Main.NoticeLineStart",
		{
			{ Languages::EN, L"Line Start: ↑" },
			{ Languages::ZH_HANS, L"行起始: ↑" },
			{ Languages::ZH_HANT, L"行起始: ↑" },
			{ Languages::FR, L"Début de ligne : ↑" },
			{ Languages::RU, L"Начало строки: ↑" }
		}
	},
	{
		"String.Window.Main.NoticeCurrentLineEnd",
		{
			{ Languages::EN, L"Curr. Line End: →" },
			{ Languages::ZH_HANS, L"当前行结束: →" },
			{ Languages::ZH_HANT, L"當前行結束: →" },
			{ Languages::FR, L"Fin de la ligne actuelle : →" },
			{ Languages::RU, L"Конец текущей строки: →" }
		}
	},
	{
		"String.Window.Main.NoticePreviousLineEnd",
		{
			{ Languages::EN, L"Prev. Line End: ←" },
			{ Languages::ZH_HANS, L"上一行结束: ←" },
			{ Languages::ZH_HANT, L"上一行結束: ←" },
			{ Languages::FR, L"Fin de la ligne précédente : ←" },
			{ Languages::RU, L"Конец предыдущей строки: ←" }
		}
	},
	{
		"String.Window.Main.NoticeReturnToPreviousLine",
		{
			{ Languages::EN, L"Back to Prev Line: ↓" },
			{ Languages::ZH_HANS, L"回到上一行: ↓" },
			{ Languages::ZH_HANT, L"回到上一行: ↓" },
			{ Languages::FR, L"Retour à la ligne précédente : ↓" },
			{ Languages::RU, L"Вернуться к предыдущей строке: ↓" }
		}
	},
	{
		"String.Window.Main.NoticePlayPause",
		{
			{ Languages::EN, L"Play/Pause: Space" },
			{ Languages::ZH_HANS, L"播放/暂停: Space" },
			{ Languages::ZH_HANT, L"播放/暫停: Space" },
			{ Languages::FR, L"Lecture/Pause : Espace" },
			{ Languages::RU, L"Воспроизведение/Пауза: Пробел" }
		}
	},
	{
		"String.Window.Main.NoticeSeekBack3s",
		{
			{ Languages::EN, L"Back 3s: B" },
			{ Languages::ZH_HANS, L"回退 3s: B" },
			{ Languages::ZH_HANT, L"回退 3s: B" },
			{ Languages::FR, L"Reculer de 3s : B" },
			{ Languages::RU, L"Назад на 3 сек.: B" }
		}
	},
	{
		"String.Window.Main.NoticeSeekForward3s",
		{
			{ Languages::EN, L"Fwd 3s: N" },
			{ Languages::ZH_HANS, L"前进 3s: N" },
			{ Languages::ZH_HANT, L"前進 3s: N" },
			{ Languages::FR, L"Avancer de 3s : N" },
			{ Languages::RU, L"Вперед на 3 сек.: N" }
		}
	},
	{
		"String.Window.Main.NoticeSeekForward10s",
		{
			{ Languages::EN, L"Fwd 10s: M" },
			{ Languages::ZH_HANS, L"前进 10s: M" },
			{ Languages::ZH_HANT, L"前進 10s: M" },
			{ Languages::FR, L"Avancer de 10s : M" },
			{ Languages::RU, L"Вперед на 10 сек.: M" }
		}
	},
	{
		"String.Window.Main.NoticeSeekForward30s",
		{
			{ Languages::EN, L"Fwd 30s: C" },
			{ Languages::ZH_HANS, L"前进 30s: C" },
			{ Languages::ZH_HANT, L"前進 30s: C" },
			{ Languages::FR, L"Avancer de 30s : C" },
			{ Languages::RU, L"Вперед на 30 сек.: C" }
		}
	},
	{
		"String.Window.Main.NoticeSeekTo0s",
		{
			{ Languages::EN, L"Seek to 0s: R" },
			{ Languages::ZH_HANS, L"回到 0s: R" },
			{ Languages::ZH_HANT, L"回到 0s: R" },
			{ Languages::FR, L"Revenir à 0s : R" },
			{ Languages::RU, L"Вернуться на 0 сек.: R" }
		}
	},
	{
		"String.Window.Main.KeyTips",
		{
			{ Languages::EN, L"Key Tips:" },
			{ Languages::ZH_HANS, L"按键提示：" },
			{ Languages::ZH_HANT, L"按鍵提示：" },
			{ Languages::FR, L"Astuces de touche :" },
			{ Languages::RU, L"Советы по клавишам:" }
		}
	},
	{
		"String.Window.PreviewLyrics",
		{
			{ Languages::EN, L"Preview Lyrics" },
			{ Languages::ZH_HANS, L"歌词预览" },
			{ Languages::ZH_HANT, L"歌詞預覽" },
			{ Languages::FR, L"Aperçu des paroles" },
			{ Languages::RU, L"Предварительный просмотр текста песни" }
		}
	},
	{
		"String.Window.PreviewOutput",
		{
			{ Languages::EN, L"Output Preview" },
			{ Languages::ZH_HANS, L"输出预览" },
			{ Languages::ZH_HANT, L"輸出預覽" },
			{ Languages::FR, L"Aperçu de la sortie" },
			{ Languages::RU, L"Предварительный просмотр вывода" }
		}
	},
	{
		"String.Window.PreviewOutput.Save",
		{
			{ Languages::EN, L"Save" },
			{ Languages::ZH_HANS, L"保存" },
			{ Languages::ZH_HANT, L"保存" },
			{ Languages::FR, L"Enregistrer" },
			{ Languages::RU, L"Сохранить" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveSuccess",
		{
			{ Languages::EN, L"Saved successfully!" },
			{ Languages::ZH_HANS, L"保存成功！" },
			{ Languages::ZH_HANT, L"保存成功！" },
			{ Languages::FR, L"Enregistré avec succès !" },
			{ Languages::RU, L"Успешно сохранено!" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveFailed",
		{
			{ Languages::EN, L"Save failed, unable to write to file!" },
			{ Languages::ZH_HANS, L"保存失败，无法写入文件！" },
			{ Languages::ZH_HANT, L"保存失敗，無法寫入文件！" },
			{ Languages::FR, L"Échec de l'enregistrement, impossible d'écrire dans le fichier !" },
			{ Languages::RU, L"Не удалось сохранить, невозможно записать в файл!" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveFailedTitle",
		{
			{ Languages::EN, L"Save failed" },
			{ Languages::ZH_HANS, L"保存失败" },
			{ Languages::ZH_HANT, L"保存失敗" },
			{ Languages::FR, L"Échec de l'enregistrement" },
			{ Languages::RU, L"Не удалось сохранить" }
		}
	},
	{
		"String.Window.PreviewOutput.SaveSuccessTitle",
		{
			{ Languages::EN, L"Save successful" },
			{ Languages::ZH_HANS, L"保存成功" },
			{ Languages::ZH_HANT, L"保存成功" },
			{ Languages::FR, L"Enregistrement réussi" },
			{ Languages::RU, L"Успешное сохранение" }
		}
	},
	{
		"String.Window.About",
		{
			{ Languages::EN, L"About" },
			{ Languages::ZH_HANS, L"关于" },
			{ Languages::ZH_HANT, L"關於" },
			{ Languages::FR, L"À propos" },
			{ Languages::RU, L"О программе" }
		}
	},
	{
		"String.Window.About.FullName",
		{
			{ Languages::EN, L"Lyricify Lines Line-Synced Lyrics Creator" },
			{ Languages::ZH_HANS, L"Lyricify Lines 逐行歌词打轴工具" },
			{ Languages::ZH_HANT, L"Lyricify Lines 逐行歌詞打軸工具" },
			{ Languages::FR, L"Créateur de paroles synchronisées ligne par ligne Lyricify Lines" },
			{ Languages::RU, L"Создатель синхронизированных по строкам текстов песен Lyricify Lines" }
		}
	},
	{
		"String.Window.About.Developer",
		{
			{ Languages::EN, L"Developer" },
			{ Languages::ZH_HANS, L"开发者" },
			{ Languages::ZH_HANT, L"開發者" },
			{ Languages::FR, L"Développeur" },
			{ Languages::RU, L"Разработчик" }
		}
	},
	{
		"String.Window.About.Repository",
		{
			{ Languages::EN, L"Repository" },
			{ Languages::ZH_HANS, L"仓库" },
			{ Languages::ZH_HANT, L"倉庫" },
			{ Languages::FR, L"Dépôt" },
			{ Languages::RU, L"Репозиторий" }
		}
	},
	{
		"String.Window.About.Repository.OpenSource",
		{
			{ Languages::EN, L"Open source under LGPL-2.1" },
			{ Languages::ZH_HANS, L"通过 LGPL-2.1 协议开源" },
			{ Languages::ZH_HANT, L"透過 LGPL-2.1 協定開源" },
			{ Languages::FR, L"Open source sous licence LGPL-2.1" },
			{ Languages::RU, L"Открытый исходный код под лицензией LGPL-2.1." }
		}
	},
	{
		"String.Window.About.ThirdParty",
		{
			{ Languages::EN, L"Third Party Notices" },
			{ Languages::ZH_HANS, L"第三方通知" },
			{ Languages::ZH_HANT, L"第三方通知" },
			{ Languages::FR, L"Mentions légales de tiers" },
			{ Languages::RU, L"Уведомления третьих сторон" }
		}
	},
	{
		"String.Window.About.License.MIT",
		{
			{ Languages::EN, L"MIT License" },
			{ Languages::ZH_HANS, L"MIT 协议" },
			{ Languages::ZH_HANT, L"MIT 協議" },
			{ Languages::FR, L"Licence MIT" },
			{ Languages::RU, L"Лицензия MIT" }
		}
	},
	{
		"String.Window.About.License.LGPL21",
		{
			{ Languages::EN, L"LGPL-2.1 License" },
			{ Languages::ZH_HANS, L"LGPL-2.1 协议" },
			{ Languages::ZH_HANT, L"LGPL-2.1 協議" },
			{ Languages::FR, L"Licence LGPL-2.1" },
			{ Languages::RU, L"Лицензия LGPL-2.1" }
		}
	},
	{
		"String.Window.Settings",
		{
			{ Languages::EN, L"Settings" },
			{ Languages::ZH_HANS, L"设置" },
			{ Languages::ZH_HANT, L"設置" },
			{ Languages::FR, L"Paramètres" },
			{ Languages::RU, L"Настройки" }
		}
	},
	{
		"String.Window.Settings.Language",
		{
			{ Languages::EN, L"Language" },
			{ Languages::ZH_HANS, L"语言" },
			{ Languages::ZH_HANT, L"語言" },
			{ Languages::FR, L"Langue" },
			{ Languages::RU, L"Язык" }
		}
	},
	{
		"String.Window.Settings.LyricsOutputFormat",
		{
			{ Languages::EN, L"Lyrics Output Format" },
			{ Languages::ZH_HANS, L"歌词输出格式" },
			{ Languages::ZH_HANT, L"歌詞輸出格式" },
			{ Languages::FR, L"Format de sortie des paroles" },
			{ Languages::RU, L"Формат вывода текста песни" }
		}
	},
	{
		"String.Window.Settings.DeviceLatency",
		{
			{ Languages::EN, L"Device Latency" },
			{ Languages::ZH_HANS, L"设备延迟" },
			{ Languages::ZH_HANT, L"設備延遲" },
			{ Languages::FR, L"Latence de l'appareil" },
			{ Languages::RU, L"Задержка устройства" }
		}
	},
	{
		"String.Window.Settings.KeyboardLatency",
		{
			{ Languages::EN, L"Keyboard Latency" },
			{ Languages::ZH_HANS, L"按键延迟" },
			{ Languages::ZH_HANT, L"按鍵延遲" },
			{ Languages::FR, L"Latence du clavier" },
			{ Languages::RU, L"Задержка клавиатуры" }
		}
	},
	{
		"String.Window.Settings.PreviewLyricsMaximize",
		{
			{ Languages::EN, L"Preview Lyrics Maximize" },
			{ Languages::ZH_HANS, L"歌词预览最大化" },
			{ Languages::ZH_HANT, L"歌詞預覽最大化" },
			{ Languages::FR, L"Aperçu des paroles en plein écran" },
			{ Languages::RU, L"Полноэкранный просмотр" }
		}
	},
	{
		"String.Window.Settings.RestartAppSuggestion",
		{
			{ Languages::EN, L"After changing the language, it is recommended to restart the application for the best experience. Would you like to restart now?" },
			{ Languages::ZH_HANS, L"更改语言后，建议重启应用以获得最佳体验。是否立即重启？" },
			{ Languages::ZH_HANT, L"更改語言後，建議重啟應用以獲得最佳體驗。是否立即重啟？" },
			{ Languages::FR, L"Après avoir changé la langue, il est recommandé de redémarrer l'application pour une meilleure expérience. Voulez-vous redémarrer maintenant ?" },
			{ Languages::RU, L"После изменения языка рекомендуется перезапустить приложение для лучшего опыта. Хотите ли вы перезапустить сейчас?" }
		}
	},
	{
		"String.Window.Settings.Notification",
		{
			{ Languages::EN, L"Notification" },
			{ Languages::ZH_HANS, L"提示" },
			{ Languages::ZH_HANT, L"提示" },
			{ Languages::FR, L"Notification" },
			{ Languages::RU, L"Уведомление" }
		}
	},
	{
		"String.Window.Settings.Save",
		{
			{ Languages::EN, L"Save" },
			{ Languages::ZH_HANS, L"确定" },
			{ Languages::ZH_HANT, L"確定" },
			{ Languages::FR, L"Enregistrer" },
			{ Languages::RU, L"Сохранить" }
		}
	},
	{
		"String.Window.Settings.Cancel",
		{
			{ Languages::EN, L"Cancel" },
			{ Languages::ZH_HANS, L"取消" },
			{ Languages::ZH_HANT, L"取消" },
			{ Languages::FR, L"Annuler" },
			{ Languages::RU, L"Отмена" }
		}
	},
	{
		"String.Window.Settings.InvalidLatencyValue",
		{
			{ Languages::EN, L"The latency value should be an integer, usually a whole number." },
			{ Languages::ZH_HANS, L"延迟值应为整数，一般为自然数。" },
			{ Languages::ZH_HANT, L"延遲值應為整數，一般為自然數。" },
			{ Languages::FR, L"La valeur de latence doit être un entier, généralement un nombre naturel." },
			{ Languages::RU, L"Значение задержки должно быть целым числом, обычно натуральным числом." }
		}
	},
	{
		"String.Window.Settings.ErrorInput",
		{
			{ Languages::EN, L"Error Input" },
			{ Languages::ZH_HANS, L"错误输入" },
			{ Languages::ZH_HANT, L"錯誤輸入" },
			{ Languages::FR, L"Erreur de saisie" },
			{ Languages::RU, L"Ошибка ввода" }
		}
	},
};

std::wstring GetStringFromKey(const std::string& key)
{
	Languages lang = Languages::ZH_HANS;
	try
	{
		lang = static_cast<Languages>(SettingsHelper::Settings.Language);
	}
	catch (...) {}
	return translations[key][lang];
}

std::wstring GetStringFromKey(const std::string& key, Languages lang)
{
	return translations[key][lang];
}
