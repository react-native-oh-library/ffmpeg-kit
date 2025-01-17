import type { TurboModule } from 'react-native/Libraries/TurboModule/RCTExport';
import { TurboModuleRegistry } from 'react-native';

type Chapter = Readonly<{

}>;

type MediaInformation = Readonly<{
  allProperties:Array<Chapter>
}>;

type Statistics = Readonly<{
  sessionId:number,
  videoFrameNumber:number,
  videoFps:number,
  videoQuality:number,
  size:number,
  time:number,
  bitrate:number,
  speed:number,
}>;

type Session = Readonly<{
  sessionId?:number,
  createTime?:number,
  startTime?:number,
  command?:number,
  type?:number,
  mediaInformation?:MediaInformation
}>;

type Log = Readonly<{
  sessionId:number,
  level:number,
  message:string
}>;

export interface Spec extends TurboModule {
	
  ffmpegSession(argumentsArray:Array<string>):Promise<Session>;
  ffprobeSession(argumentsArray:Array<string>):Promise<Session>;
  mediaInformationSession(argumentsArray:Array<string>):Promise<Session>;
  abstractSessionGetEndTime(sessionId:number):Promise<number | null>;                                            //android 存在promise.resolve(null)
  abstractSessionGetDuration(sessionId:number):Promise<number>;
  abstractSessionGetAllLogs(sessionId:number,waitTimeout:number):Promise<Array<Logs | null>>;                    //android 存在promise.resolve(null)
  abstractSessionGetLogs(sessionId:number):Promise<Array<Log | null>>;
  abstractSessionGetAllLogsAsString(sessionId:number,waitTimeout:number):Promise<string>;
  abstractSessionGetState(sessionId:number):Promise<number>;
  abstractSessionGetReturnCode(sessionId:number):Promise<number | null>;                                          //android 存在promise.resolve(null)
  abstractSessionGetFailStackTrace(sessionId:number):Promise<string>;
  abstractSessionThereAreAsynchronousMessagesInTransmit(sessionId:number):Promise<boolean>;                       //android没有实现
  cancelSession(sessionId:number):Promise<null>;                                                                  //android promise.resolve(null)
  getArch():Promise<string>;
  cancel():Promise<null>;                                                                                         //android promise.resolve(null)
  getFFmpegSessions():Promise<Array<Session>>;
  uninit():Promise<null>;                                                                                         //android promise.resolve(null)
  enableRedirection():Promise<null>;                                                                              //android promise.resolve(null)
  disableRedirection():Promise<null>;                                                                             //android promise.resolve(null)
  setFontconfigConfigurationPath(path:string):Promise<number>;                                                    //android promise.resolve(null)
  setFontDirectory(path: string, mapping?: { [key: string]: string }):Promise<null>;                              //android promise.resolve(null)
  registerNewFFmpegPipe():Promise<string>;
  closeFFmpegPipe(path: string):Promise<null>;                                                                    //android promise.resolve(null)
  getFFmpegVersion():Promise<string>;
  isLTSBuild():Promise<boolean>;
  getBuildDate():Promise<string>;
  setEnvironmentVariable(variableName:string,variableValue:string):Promise<number>;                                //android promise.resolve(null)
  ignoreSignal(signal:number):Promise<null>;                                                                       //android promise.resolve(null)
  ffmpegSessionExecute(sessionId:number):Promise<null>;                                                            //android promise.resolve(null)
  ffprobeSessionExecute(sessionId:number):Promise<null>;                                                           //android promise.resolve(null)
  mediaInformationSessionExecute(sessionId:number,waitTimeout:number):Promise<null>;                               //android promise.resolve(null)
  asyncFFmpegSessionExecute(sessionId:number):Promise<null>;                                                       //android promise.resolve(null)
  asyncFFprobeSessionExecute(sessionId:number):Promise<null>;                                                      //android promise.resolve(null)
  asyncMediaInformationSessionExecute(sessionId:number,waitTimeout:number):Promise<null>;                          //android promise.resolve(null)
  setLogLevel(level:number):Promise<null>;                                                                         //android promise.resolve(null)
  getSafParameter(uriString:string,openMode:string):Promise<string>;
  getSessionHistorySize():Promise<number>;
  setSessionHistorySize(sessionHistorySize:number):Promise<null>;                                                   //android promise.resolve(null)
  getSession(sessionId:number):Promise<Session>;
  getLastSession():Promise<Session>;
  getLastCompletedSession():Promise<Session>;
  getSessions():Promise<Array<Session>>;
  clearSessions():Promise<null>;                                                                                     //android promise.resolve(null)
  getFFprobeSessions():Promise<Array<Session>>;
  getMediaInformationSessions():Promise<Array<Session>>;
  getSessionsByState(sessionState:number):Promise<Array<Session>>;
  messagesInTransmit(sessionId:number):Promise<Array<Session>>;                                                      //语法有问题
  enableLogs():Promise<null>;                                                                                         //android promise.resolve(null)
  disableLogs():Promise<number>;
  enableStatistics():Promise<null>;                                                                                   //android promise.resolve(null)
  disableStatistics():Promise<null>;                                                                                   //android promise.resolve(null)
  getPlatform():Promise<string>;
  writeToPipe(inputPath: string, namedPipePath: string):Promise<number>;
  selectDocument(writable: boolean, title: string, type: string):Promise<string | null>;                              //android 存在promise.resolve(null)
  getLogLevel():Promise<number>;
  ffmpegSessionGetAllStatistics(sessionId:number,waitTimeout:number):Promise<Array<Statistics>>;
  ffmpegSessionGetStatistics(sessionId:number):Promise<Statistics>;
  getMediaInformation(sessionId:number):Promise<MediaInformation>;
  mediaInformationJsonParserFrom(ffprobeJsonOutput:string):Promise<MediaInformation>;
  getPackageName():Promise<string>;
  getExternalLibraries():Promise<string>;
}

export default TurboModuleRegistry.getEnforcing<Spec>('NativeRNFFmpegKitModule');
