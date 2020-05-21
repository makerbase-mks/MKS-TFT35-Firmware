#include "gui.h"
#include "button.h"
#include "draw_ui.h"
#include "at24cxx.h"
#include "mks_tft_com.h"


#ifndef GUI_FLASH
#define GUI_FLASH
#endif


//#if 1//HAS_PID_HEATING
//  #define PID_K2 (1.0-PID_K1)
//  //#define PID_dT ((OVERSAMPLENR * float(ACTUAL_ADC_SAMPLES)) / (F_CPU / 64.0 / 256.0))
//	#define PID_dT	0.16384
//
//  // Apply the scale factors to the PID values
//  #define scalePID_i(i)   ( (i) * PID_dT )
//  #define unscalePID_i(i) ( (i) / PID_dT )
//  #define scalePID_d(d)   ( (d) / PID_dT )
//  #define unscalePID_d(d) ( (d) * PID_dT )
//#endif

static GUI_HWIN hNumberKeyWnd;
static BUTTON_STRUCT NumberKey_1,NumberKey_2,NumberKey_3,NumberKey_4,NumberKey_5;
static BUTTON_STRUCT NumberKey_6,NumberKey_7,NumberKey_8,NumberKey_9,NumberKey_0;
static BUTTON_STRUCT KeyPoint,KeyConfirm,KeyReset,KeyBack;
static BUTTON_STRUCT KeyValue,Nagetive;

static TEXT_Handle textKeyNumb;


inline void gcode_M500() {
//  (void)settings.save();
}

char key_value[11]={0};
static char cnt=0;
static char point_flg = 1;
void set_value_confirm();

static void cbNumberKeyWin(WM_MESSAGE * pMsg) {

    struct PressEvt *press_event;
    switch (pMsg->MsgId)
    {
    	case WM_PAINT:

    		break;
    	case WM_TOUCH:
    	 	press_event = (struct PressEvt *)pMsg->Data.p;
    		
    		break;
    	case WM_TOUCH_CHILD:
    		press_event = (struct PressEvt *)pMsg->Data.p;

    		break;
    		
    	case WM_NOTIFY_PARENT:
    		if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)
    		{
                 
    			if(pMsg->hWinSrc == NumberKey_1.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='1';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }

    			}
    			else if(pMsg->hWinSrc == NumberKey_2.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='2';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }	
    			}
    			else if(pMsg->hWinSrc == NumberKey_3.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='3';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }

    			}  
    			else if(pMsg->hWinSrc == NumberKey_4.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='4';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }

    			}  
    			else if(pMsg->hWinSrc == NumberKey_5.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='5';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }

    			} 
    			else if(pMsg->hWinSrc == NumberKey_6.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='6';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }

    			}  
    			else if(pMsg->hWinSrc == NumberKey_7.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='7';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }

    			} 
    			else if(pMsg->hWinSrc == NumberKey_8.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='8';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }

    			} 
    			else if(pMsg->hWinSrc == NumberKey_9.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='9';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }

    			}
    			else if(pMsg->hWinSrc == NumberKey_0.btnHandle)
    			{
                    if(cnt<=10)
                    {         
                        key_value[cnt]='0';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }

    			}  
    			else if(pMsg->hWinSrc == KeyPoint.btnHandle)
    			{
                    if((cnt!=0)&&(point_flg==1))
                    {  
                        point_flg = 0;
                        key_value[cnt]='.';
                        TEXT_SetText(textKeyNumb, key_value);
                        cnt++;
                    }
    			}
    			else if(pMsg->hWinSrc == KeyBack.btnHandle)
    			{
                    if(cnt>0)
                    {   
                       cnt--;  
                    }
                    if(key_value[cnt]=='.')point_flg=1;
                    key_value[cnt]=0;
                    TEXT_SetText(textKeyNumb, key_value);

    			}
    			else if(pMsg->hWinSrc == KeyReset.btnHandle)
    			{
                    //if(cnt<=10)
                    {        
                        memset(key_value,0,sizeof(key_value));
                        cnt=0;
                        key_value[cnt]='0';
                        point_flg = 1;
                        TEXT_SetText(textKeyNumb, key_value);
                        
                    }

    			}   
			else if(pMsg->hWinSrc == Nagetive.btnHandle)
			{
				if(cnt==0)
	                    {         
	                        key_value[cnt]='-';
	                        TEXT_SetText(textKeyNumb, key_value);
	                        cnt++;
	                    }
			}
    			else if(pMsg->hWinSrc == KeyConfirm.btnHandle)
    			{
    				last_disp_state = NUMBER_KEY_UI;
                    if(strlen(key_value)!=0)
                       set_value_confirm();
                    Clear_NumberKey();
                    draw_return_ui();
    			}  
               
    		}
    		break;
    		
    	default:
    		WM_DefaultProc(pMsg);
    	}
}
void set_value_confirm()
{
	char buf[30]={0};

    switch(value)
    {
		case X_stroke:
		break;
		case X_stroke_min:
		break;
		case Y_stroke_min:
		break;
		case Z_stroke_min:
		break;
		case Y_stroke:
		break;
		case Z_stroke:
		break;
		case Load_Temper_limit:
			gCfgItems.filament_limit_temper = atoi(key_value);
			HAL::AT24CXX_Write(BAK_FILAMENT_LIMIT_TERMPER_ADDR,(uint8_t *)&gCfgItems.filament_limit_temper,2); 
		break;
		case Load_Speed:
			gCfgItems.filament_load_speed = atoi(key_value);
			gCfgItems.filament_loading_time = (uint32_t)((gCfgItems.filament_load_length*60.0/gCfgItems.filament_load_speed)+0.5);
			HAL::AT24CXX_Write(BAK_FILAMENT_LOAD_SPEED_ADDR,(uint8_t *)&gCfgItems.filament_load_speed,2);	
		break;
		case Load_Length:
			gCfgItems.filament_load_length = atoi(key_value);
			gCfgItems.filament_loading_time = (uint32_t)((gCfgItems.filament_load_length*60.0/gCfgItems.filament_load_speed)+0.5);
			HAL::AT24CXX_Write(BAK_FILAMENT_LOAD_LENGTH_ADDR,(uint8_t *)&gCfgItems.filament_load_length,2); 
		break;   
		case Unload_Temper_limit:
		break;
		case Unload_Speed:
			gCfgItems.filament_unload_speed = atoi(key_value);    
			gCfgItems.filament_unloading_time = (uint32_t)((gCfgItems.filament_unload_length*60.0/gCfgItems.filament_unload_speed)+0.5);	   
			HAL::AT24CXX_Write(BAK_FILAMENT_UNLOAD_SPEED_ADDR,(uint8_t *)&gCfgItems.filament_unload_speed,2);	 
		break;
		case Unload_Length:
			gCfgItems.filament_unload_length = atoi(key_value);
			HAL::AT24CXX_Write(BAK_FILAMENT_UNLOAD_LENGTH_ADDR,(uint8_t *)&gCfgItems.filament_unload_length,2); 
			gCfgItems.filament_unloading_time = (uint32_t)((gCfgItems.filament_unload_length*60.0/gCfgItems.filament_unload_speed)+0.5);
		break;
		case xoffset:
		        gCfgItems.xProbeOffset = atof(key_value);   
				memset(buf,0,sizeof(buf));
				sprintf(buf, "M851 X%0.2f\n",gCfgItems.xProbeOffset );
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);     
		break; 
		case yoffset:
		        gCfgItems.yProbeOffset = atof(key_value);   
				memset(buf,0,sizeof(buf));
				sprintf(buf, "M851 Y%0.2f\n",gCfgItems.yProbeOffset );
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);  				
		break;
		case zoffset:
		        gCfgItems.zProbeOffset = atof(key_value); 	
				
				if((gCfgItems.zProbeOffset<0) && ( (-gCfgItems.zProbeOffset) > ZPROBEOFFSET_MAX ) )
				{
						gCfgItems.zProbeOffset = -ZPROBEOFFSET_MAX;
				}
				if((gCfgItems.zProbeOffset>0) && ( gCfgItems.zProbeOffset > ZPROBEOFFSET_MAX ) )
						gCfgItems.zProbeOffset = ZPROBEOFFSET_MAX;
				
				memset(buf,0,sizeof(buf));
				sprintf(buf, "M851 Z%0.2f\n",gCfgItems.zProbeOffset );
				pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);  				
		break; 
		case xyspeed:
		//        mksCfg.xy_probe_speed = atof(key_value);   
		//        epr_write_data(EPR_XY_PROBE_SPEED, (uint8_t *)&mksCfg.xy_probe_speed,sizeof(float));
		break;
		case zspeed:
		//        mksCfg.z_probe_speed_fast = atof(key_value);   
		//        epr_write_data(EPR_Z_PROBE_SPEED_FAST, (uint8_t *)&mksCfg.z_probe_speed_fast,sizeof(float));
		//        mksCfg.z_probe_speed_slow= (float)((uint32_t)mksCfg.z_probe_speed_fast>>1);  //慢速为快速的一半 
		//        epr_write_data(EPR_Z_PROBE_SPEED_SLOW, (uint8_t *)&mksCfg.z_probe_speed_slow,sizeof(float));
		break; 
		case DeltaRadius:
		//        delta_radius=atof(key_value);
		//        gcode_M500();	//保存参数
		break;
		case DeltaDiagonalRod:
		//        delta_diagonal_rod=atof(key_value);
		//        gcode_M500();	//保存参数       
		break;
		case PrintableRadius:
		//        mksCfg.delta_printable_radius=atof(key_value);
		//        epr_write_data(EPR_DELTA_PRINTABLE_RADIUS,(uint8_t *)&mksCfg.delta_printable_radius,sizeof(float));        
		break;
		case DeltaHeight:
		//        mksCfg.delta_height=atof(key_value);
		//        epr_write_data(EPR_DELTA_HEIGHT,(uint8_t *)&mksCfg.delta_height,sizeof(float));        

		break;   
		case SmoothRodOffset:
		break;  
		case EffectorOffset:
		break;  
		case CalibrationRadius:
		break; 
		case Point1_x:
			gCfgItems.leveling_point1_x=atoi(key_value);
			HAL::AT24CXX_Write(BAK_LEVELING_POINT1_X_ADDR,(uint8_t *)&gCfgItems.leveling_point1_x,2);
		break;   
		case Point1_y:
			gCfgItems.leveling_point1_y=atof(key_value);
			HAL::AT24CXX_Write(BAK_LEVELING_POINT1_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point1_y,2);  
		break; 
		case Point2_x:
			gCfgItems.leveling_point2_x=atoi(key_value);     
			HAL::AT24CXX_Write(BAK_LEVELING_POINT2_X_ADDR,(uint8_t *)&gCfgItems.leveling_point2_x,2);
		break;   
		case Point2_y:
			gCfgItems.leveling_point2_y=atoi(key_value);
			HAL::AT24CXX_Write(BAK_LEVELING_POINT2_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point2_y,2);
		break;   
		case Point3_x:
			gCfgItems.leveling_point3_x=atoi(key_value);
			HAL::AT24CXX_Write(BAK_LEVELING_POINT3_X_ADDR,(uint8_t *)&gCfgItems.leveling_point3_x,2);
		break;   
		case Point3_y:
			gCfgItems.leveling_point3_y=atoi(key_value);
			HAL::AT24CXX_Write(BAK_LEVELING_POINT3_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point3_y,2);  
		break;  
		case Point4_x:
			gCfgItems.leveling_point4_x=atoi(key_value); 
			HAL::AT24CXX_Write(BAK_LEVELING_POINT4_X_ADDR,(uint8_t *)&gCfgItems.leveling_point4_x,2);

		break;   
		case Point4_y:
			gCfgItems.leveling_point4_y=atoi(key_value);
			HAL::AT24CXX_Write(BAK_LEVELING_POINT4_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point4_y,2);  

		break; 
		case Point5_x:
			gCfgItems.leveling_point5_x=atoi(key_value);
			HAL::AT24CXX_Write(BAK_LEVELING_POINT5_X_ADDR,(uint8_t *)&gCfgItems.leveling_point5_x,2);
		break;   
		case Point5_y:
			gCfgItems.leveling_point5_y=atoi(key_value);
			HAL::AT24CXX_Write(BAK_LEVELING_POINT5_Y_ADDR,(uint8_t *)&gCfgItems.leveling_point5_y,2);  

		break; 
		case XMaxFeedRate:
			gCfgItems.xMaxFeedRate =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M203 X%d\n",gCfgItems.xMaxFeedRate );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);         
		break;
		case YMaxFeedRate:
			gCfgItems.yMaxFeedRate =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M203 Y%d\n",gCfgItems.yMaxFeedRate );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);       
		break; 
		case ZMaxFeedRate: 
			gCfgItems.zMaxFeedRate =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M203 Z%d\n",gCfgItems.zMaxFeedRate );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
		break;  
		case E0MaxFeedRate:  
			gCfgItems.e0_MaxFeedRate =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M203 T0 E%d\n",gCfgItems.e0_MaxFeedRate );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
		break;
		case E1MaxFeedRate:
			gCfgItems.e1_MaxFeedRate =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M203 T1 E%d\n",gCfgItems.e1_MaxFeedRate );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);         
		break;   
		case PrintAcceleration:
			gCfgItems.printAccel =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M204 P%d\n",gCfgItems.printAccel );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);  
		break;   
		case RetractAcceleration:   
			gCfgItems.retractAccel =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M204 R%d\n",gCfgItems.retractAccel );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
		break;   
		case TravelAcceleration:             
		gCfgItems.travelAccel =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M204 T%d\n",gCfgItems.travelAccel );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
			break;  
		case XAcceleration:           
			gCfgItems.xMaxAccel =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M201 X%d\n",gCfgItems.xMaxAccel );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
		break; 
		case YAcceleration:      
			gCfgItems.yMaxAccel =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M201 Y%d\n",gCfgItems.yMaxAccel );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);

		break; 
		case ZAcceleration:   
			gCfgItems.zMaxAccel =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M201 Z%d\n",gCfgItems.zMaxAccel );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);     
		break;
		case E0Acceleration:     
			gCfgItems.e0_MaxAccel =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M201 T0 E%d\n",gCfgItems.e0_MaxAccel );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);      
		break; 
		case E1Acceleration:
			gCfgItems.e1_MaxAccel =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M201 T1 E%d\n",gCfgItems.e1_MaxAccel );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);     
		break;  
		case XJerk: 
		break; 
		case YJerk:
		break; 
		case ZJerk:
		break; 
		case EJerk:
		break; 
		case Xstep:
			gCfgItems.xStep	= atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M92 X%.2f\n", gCfgItems.xStep);
			pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);           
		break;
		case Ystep:
			gCfgItems.yStep =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M92 Y%0.2f\n",gCfgItems.yStep );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);     
		break;  
		case Zstep:
			gCfgItems.zStep = atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M92 Z%.2f\n", gCfgItems.zStep);
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);        
		break;  
		case E0step:
			gCfgItems.e0Step = atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M92 T0 E%.2f\n", gCfgItems.e0Step);
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);   
		break;
		case E1step:
			gCfgItems.e1Step = atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M92 T1 E%.2f\n", gCfgItems.e1Step);
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);         
		break;  
		case XYspeed:
		break;
		case Zspeed:
		break;	
		case Nozzle_Cnt:
			gCfgItems.sprayerNum=atoi(key_value);
			if(gCfgItems.sprayerNum>2)
			gCfgItems.sprayerNum=2;
			if(gCfgItems.sprayerNum<1)
			gCfgItems.sprayerNum=1;
			HAL::AT24CXX_Write(BAK_SPRAYER_NUM_ADDR,(uint8_t *)&gCfgItems.sprayerNum,1);
		break;

		case Nozzle_min:
		break;
		case Nozzle_max:
			gCfgItems.preheat_max_desireSprayerTemp=atoi(key_value);					//gCfgItems.preheat_max_desireSprayerTemp
			HAL::AT24CXX_Write(BAK_SPRAYER1_MAXTEMP_ADDR,(uint8_t *)&gCfgItems.preheat_max_desireSprayerTemp,2);	
		break;
		case Extrude_min_temper:
		break;
		//         case Nozzle_pid_p:
		////            thermalManager.Kp=atof(key_value);
		////            gcode_M500();   //保存参数   
		//			  gCfgItems.nozzle_Kp=atof(key_value);
		//			  gcode_M500();   //保存参数	
		//
		//            break;
		//         case Nozzle_pid_i:
		////            thermalManager.Ki=scalePID_i(atof(key_value));
		////            gcode_M500();   //保存参数       
		//			  gCfgItems.nozzle_Ki=scalePID_i(atof(key_value));
		//			  gcode_M500();   //保存参数
		//
		//            break;
		//         case Nozzle_pid_d:
		////            thermalManager.Kd=scalePID_d(atof(key_value));
		////            gcode_M500();   //保存参数         
		//			  gCfgItems.nozzle_Kd =scalePID_d(atof(key_value));
		//			  gcode_M500();   //保存参数 
		//
		//            break;  

		case HotBed_max:
		//          mksCfg.bed_maxtemp=atof(key_value);
			gCfgItems.preheat_max_desireBedTemp = atof(key_value);
			HAL::AT24CXX_Write(BAK_BED_MAXTEMP_ADDR,(uint8_t *)&gCfgItems.preheat_max_desireBedTemp,2); 	

		break;
		case HotBed_min:
		//          mksCfg.bed_mintemp=atof(key_value);
//			gCfgItems.preheat_min_desireBedTemp = atof(key_value);
		break;

		//         case HotBed_pid_p:
		////            thermalManager.bedKp=atof(key_value);
		////            gcode_M500();   //保存参数
		//
		//			  gCfgItems.bedKp=atof(key_value);
		//			  gcode_M500();   //保存参数
		//
		//
		//            break;
		//         case HotBed_pid_i:
		////            thermalManager.bedKi=scalePID_i(atof(key_value));
		////            gcode_M500();   //保存参数           
		//			  gCfgItems.bedKi=scalePID_i(atof(key_value));
		//			  gcode_M500();   //保存参数		 
		//
		//            break;
		//         case HotBed_pid_d:
		////            thermalManager.bedKd=scalePID_d(atof(key_value));
		////            gcode_M500();   //保存参数     
		//			  gCfgItems.bedKd=scalePID_d(atof(key_value));
		//			  gcode_M500();   //保存参数	
		//			  break;
		case Break_Z_error:
			gCfgItems.breakpoint_z_error=atof(key_value);
			HAL::AT24CXX_Write(BAK_BREAKPOINT_Z_ERROR_ADDR,(uint8_t *)&gCfgItems.breakpoint_z_error,4);	   
		break;
		case z_speed_level:		 
			gCfgItems.leveling_z_speed = atof(key_value);	   
			HAL::AT24CXX_Write(BAK_LEVELING_Z_SPEED_ADDR,(uint8_t *)&gCfgItems.leveling_z_speed,2); 

		break;
		case xy_speed_level:   
			gCfgItems.leveling_xy_speed=atof(key_value); 
			HAL::AT24CXX_Write(BAK_LEVELING_XY_SPEED_ADDR,(uint8_t *)&gCfgItems.leveling_xy_speed,2);	
		break;
		case z_high_level:
			gCfgItems.leveling_z_high=atof(key_value); 
			HAL::AT24CXX_Write(BAK_LEVELING_Z_HIGH_ADDR,(uint8_t *)&gCfgItems.leveling_z_high,2); 
		break;       
		case Points_count:
			gCfgItems.leveling_point_number=atof(key_value); 
			HAL::AT24CXX_Write(BAK_LEVELING_POINT_NUMBER_ADDR,(uint8_t *)&gCfgItems.leveling_point_number,1);   
		break;
		case Position_x:	 
			gCfgItems.Pause_XPOS = atof(key_value);
			HAL::AT24CXX_Write(BAK_PAUSE_XPOS_ADDR,(uint8_t *)&gCfgItems.Pause_XPOS,2);
		break;
		case Position_y:
			gCfgItems.Pause_YPOS = atof(key_value);
			HAL::AT24CXX_Write(BAK_PAUSE_YPOS_ADDR,(uint8_t *)&gCfgItems.Pause_YPOS,2);					 

		break; 
		case Position_z:
			gCfgItems.Pause_ZADD = atof(key_value);
			gcode_M500();
			HAL::AT24CXX_Write(BAK_PAUSE_ZADD_ADDR,(uint8_t *)&gCfgItems.Pause_ZADD,2);

		break;	
		case more_func_cnt:
			gCfgItems.morefunc_cnt = atof(key_value);
			if(gCfgItems.morefunc_cnt >= 7)
				gCfgItems.MoreItem_pic_cnt = 7;
			if (gCfgItems.MoreItem_pic_cnt<0)
				gCfgItems.MoreItem_pic_cnt = 0;
			HAL::AT24CXX_Write(BAK_PRINTING_MOREFUNC_CNT_ADDR,(uint8_t *)&gCfgItems.morefunc_cnt ,1);
		break;
		case more_btn_cnt:
			gCfgItems.MoreItem_pic_cnt = atof(key_value);
			if(gCfgItems.MoreItem_pic_cnt >= 7)
			{
//				if(gCfgItems.zoffset_display_flg == 1)
//				{
//					gCfgItems.MoreItem_pic_cnt = 6;
//				}
//				else 
					gCfgItems.MoreItem_pic_cnt = 7;
			}
//			if (gCfgItems.MoreItem_pic_cnt<0)
//			gCfgItems.MoreItem_pic_cnt = 0;
			HAL::AT24CXX_Write(BAK_MOREITEM_PIC_CNT,(uint8_t *)&gCfgItems.MoreItem_pic_cnt ,1);
		break;
//		case wifi_port:
//			gCfgItems.cloud_port = atof(key_value);
//		break;
		case btn_textOffset:
			gCfgItems.btn_text_offset = atof(key_value);
			HAL::AT24CXX_Write(BAK_BTN_TEXT_OFFSET_ADDR,(uint8_t *)&gCfgItems.btn_text_offset,1);
		break;	
		case current_x:
			gCfgItems.xCurrent = atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M906 X%d\n", gCfgItems.xCurrent);
			pushFIFO(&gcodeCmdTxFIFO, (unsigned char *)buf);		  
		break;
		case current_y:
			gCfgItems.yCurrent =atof(key_value);	
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M906 Y%d\n",gCfgItems.yCurrent );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);	  
		break;	
		case current_z:
			gCfgItems.zCurrent = atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M906 Z%d\n", gCfgItems.zCurrent);
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);		  
		break;	
		case current_E0:
			gCfgItems.e0Current = atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M906 T0 E%d\n", gCfgItems.e0Current);
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);	  
			break;
		case current_E1:
			gCfgItems.e1Current = atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M906 T1 E%d\n", gCfgItems.e1Current);
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);		  
		break;	
		case Sensivisity_X:           
			gCfgItems.xSensivisity =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M914 X%d\n",gCfgItems.xSensivisity );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);
		break; 
		case Sensivisity_Y:      
			gCfgItems.ySensivisity =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M914 Y%d\n",gCfgItems.ySensivisity );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);

		break; 
		case Sensivisity_Z:   
			gCfgItems.zSensivisity =atof(key_value);
			memset(buf,0,sizeof(buf));
			sprintf(buf, "M914 Z%d\n",gCfgItems.zSensivisity );
			pushFIFO(&gcodeCmdTxFIFO,(unsigned char *) buf);     
		break;
    }    
}
void disp_value()
{
    char *temp;
    
    switch(value)
    {
       case X_stroke:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",mksCfg.x_max_pos);
        break;
       case Y_stroke:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",mksCfg.y_max_pos); 
        break;
       case Z_stroke:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",mksCfg.z_max_pos);
        break; 
       case Load_Temper_limit:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_limit_temper);
        break;
       case Load_Speed:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_load_speed);       
        break;
       case Load_Length:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_load_length);        
        break;
       case Unload_Temper_limit:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%d",gCfgItems.filament_unload_limit_temper);
        break;
       case Unload_Speed:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_unload_speed);       
        break;
       case Unload_Length:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.filament_unload_length);        
        break;   
       case xoffset:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%.1f",gCfgItems.xProbeOffset);       
        break;  
       case yoffset:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%.1f",gCfgItems.yProbeOffset);       
        break;  
       case zoffset:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%.1f",gCfgItems.zProbeOffset);       
        break; 
       case xyspeed:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",mksCfg.xy_probe_speed);       
        break; 
       case zspeed:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",mksCfg.z_probe_speed_fast);       
        break; 
       case DeltaRadius:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",delta_radius);
        break;
       case DeltaDiagonalRod:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",delta_diagonal_rod);        
        break;
       case PrintableRadius:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",mksCfg.delta_printable_radius);        
        break;
       case DeltaHeight:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",mksCfg.delta_height);        
        break;   
       case SmoothRodOffset:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",mksCfg.delta_smooth_rod_offset);        
        break;  
       case EffectorOffset:
//        memset(cmd_code,0,sizeof(cmd_code));
//        sprintf(cmd_code,"%.1f",mksCfg.delta_effector_offset);        
        break;  
       case CalibrationRadius:
//        memset(cmd_code,0,sizeof(cmd_code));
////        sprintf(cmd_code,"%.1f",delta_calibration_radius);        
        break; 
       case Point1_x:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point1_x);        
        break; 
	case Point1_y:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point1_y);        
        break;
       case Point2_x:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point2_x);        
        break;
	case Point2_y:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point2_y);        
        break;
       case Point3_x:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point3_x);        
        break;   
	case Point3_y:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point3_y);        
        break;
       case Point4_x:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point4_x);        
        break; 
	case Point4_y:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point4_y);        
        break; 
	case Point5_x:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point5_x);        
        break; 
	case Point5_y:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.leveling_point5_y);        
        break;
       case XMaxFeedRate:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.xMaxFeedRate);        
        break;
       case YMaxFeedRate:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.yMaxFeedRate);        
        break; 
       case ZMaxFeedRate:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.zMaxFeedRate);        
        break;  
       case E0MaxFeedRate:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.e0_MaxFeedRate);        
        break;
       case E1MaxFeedRate:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%.1f",gCfgItems.e1_MaxFeedRate);        
        break;
       case PrintAcceleration:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.printAccel);       
        break;   
       case RetractAcceleration:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.retractAccel);       
        break;   
       case TravelAcceleration:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.travelAccel);       
        break;  
       case XAcceleration:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.xMaxAccel);       
        break; 
       case YAcceleration:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.yMaxAccel);       
        break; 
       case ZAcceleration:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.zMaxAccel);       
        break;
       case E0Acceleration:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.e0_MaxAccel);       
        break; 
       case E1Acceleration:
        memset(cmd_code,0,sizeof(cmd_code));
        sprintf(cmd_code,"%d",gCfgItems.e1_MaxAccel);       
        break;
       case XJerk:
//       memset(cmd_code,0,sizeof(cmd_code));
//       sprintf(cmd_code,"%.1f",planner.max_jerk[X_AXIS]);

        break;
       case YJerk:
//       memset(cmd_code,0,sizeof(cmd_code));
//       sprintf(cmd_code,"%.1f",planner.max_jerk[Y_AXIS]);

        break; 
       case ZJerk:
//       memset(cmd_code,0,sizeof(cmd_code));
//       sprintf(cmd_code,"%.1f",planner.max_jerk[Z_AXIS]);

        break; 
       case EJerk:
//       memset(cmd_code,0,sizeof(cmd_code));
//       sprintf(cmd_code,"%.1f",planner.max_jerk[E_AXIS]);

        break; 
       case Xstep:
		   memset(cmd_code,0,sizeof(cmd_code));
		//       sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[X_AXIS]);
		   sprintf(cmd_code,"%.1f",gCfgItems.xStep);

        break; 
       case Ystep:
       memset(cmd_code,0,sizeof(cmd_code));
//       sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[Y_AXIS]);
	   sprintf(cmd_code,"%.1f",gCfgItems.yStep);

        break;  
       case Zstep:
	       memset(cmd_code,0,sizeof(cmd_code));
	//       sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[Z_AXIS]);
		   sprintf(cmd_code,"%.1f",gCfgItems.zStep);

        break; 
       case E0step:
	       memset(cmd_code,0,sizeof(cmd_code));
	//       sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[E_AXIS]);
		   sprintf(cmd_code,"%.1f",gCfgItems.e0Step);

        break; 
       case E1step:
	       memset(cmd_code,0,sizeof(cmd_code));
	//       sprintf(cmd_code,"%.1f",planner.axis_steps_per_mm[XYZE]);
		   sprintf(cmd_code,"%.1f",gCfgItems.e1Step);

        break;  
       case XYspeed:
//		memset(cmd_code,0,sizeof(cmd_code));
//		sprintf(cmd_code,"%.1f",mksCfg.homing_feedrate_xy);

        break;
       case Zspeed:
//		memset(cmd_code,0,sizeof(cmd_code));
//		sprintf(cmd_code,"%.1f",mksCfg.homing_feedrate_z);

        break;

       case Nozzle_Cnt:
	        memset(cmd_code,0,sizeof(cmd_code));
	//        sprintf(cmd_code,"%d",mksCfg.extruders);  //gCfgItems.sprayerNum      
		    sprintf(cmd_code,"%d",gCfgItems.sprayerNum);
        break;
       case Nozzle_min:
//	        memset(cmd_code,0,sizeof(cmd_code));
	//        sprintf(cmd_code,"%d",mksCfg.heater_0_mintemp);         
//		  	sprintf(cmd_code,"%d", gCfgItems.preheat_min_desireSprayerTemp); 

        break;
       case Nozzle_max:
	        memset(cmd_code,0,sizeof(cmd_code));
	//        sprintf(cmd_code,"%d",mksCfg.heater_0_maxtemp);         
		    sprintf(cmd_code,"%d",gCfgItems.preheat_max_desireSprayerTemp);	   
        break;
       case Extrude_min_temper:
//        memset(cmd_code,0,sizeof(cmd_code));
//		sprintf(cmd_code,"%d", gCfgItems.preheat_min_desireSprayerTemp); 

        break;
//       case Nozzle_pid_p:
////        memset(cmd_code,0,sizeof(cmd_code));
////        sprintf(cmd_code,"%.3f",thermalManager.Kp);
//		  memset(cmd_code,0,sizeof(cmd_code));
//		  sprintf(cmd_code,"%.3f",gCfgItems.nozzle_Kp);
//
//        break;
//       case Nozzle_pid_i:
////        memset(cmd_code,0,sizeof(cmd_code));
////        sprintf(cmd_code,"%.3f",unscalePID_i(thermalManager.Ki));
//		memset(cmd_code,0,sizeof(cmd_code));
//		sprintf(cmd_code,"%.3f",gCfgItems.nozzle_Ki);
//
//        break;
//       case Nozzle_pid_d:
////        memset(cmd_code,0,sizeof(cmd_code));
////        sprintf(cmd_code,"%.3f",unscalePID_d(thermalManager.Kd));
//		memset(cmd_code,0,sizeof(cmd_code));
//		sprintf(cmd_code,"%.3f",gCfgItems.nozzle_Kd);
//
//        break; 
        
       case HotBed_max:
         memset(cmd_code,0,sizeof(cmd_code));
//         sprintf(cmd_code,"%d",mksCfg.bed_maxtemp);         
	   	sprintf(cmd_code,"%d",gCfgItems.preheat_max_desireBedTemp);		  

         break;
	case HotBed_min:
 //        memset(cmd_code,0,sizeof(cmd_code));
//         sprintf(cmd_code,"%d",mksCfg.bed_mintemp);         
//		sprintf(cmd_code,"%d",gCfgItems.preheat_min_desireBedTemp);		   

         break;
		
//       case HotBed_pid_p:
////        memset(cmd_code,0,sizeof(cmd_code));
////        sprintf(cmd_code,"%.3f",thermalManager.bedKp);
//		  memset(cmd_code,0,sizeof(cmd_code));
//		  sprintf(cmd_code,"%.3f",gCfgItems.bedKp);
//
//        break;
//       case HotBed_pid_i:
////        memset(cmd_code,0,sizeof(cmd_code));
////        sprintf(cmd_code,"%.3f",unscalePID_i(thermalManager.bedKi));
//		  memset(cmd_code,0,sizeof(cmd_code));
//		  sprintf(cmd_code,"%.3f",gCfgItems.bedKi);
//
//        break;
//       case HotBed_pid_d:
////        memset(cmd_code,0,sizeof(cmd_code));
////        sprintf(cmd_code,"%.3f",unscalePID_d(thermalManager.bedKd));
//		  memset(cmd_code,0,sizeof(cmd_code));
//		  sprintf(cmd_code,"%.3f",gCfgItems.bedKd);
//	   	break;
	 	case Break_Z_error:
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%.3f",gCfgItems.breakpoint_z_error);
		break;
		case z_speed_level:		  
			memset(cmd_code,0,sizeof(cmd_code));
		 	sprintf(cmd_code,"%d",gCfgItems.leveling_z_speed);
		
		break;
		case xy_speed_level:	 
			memset(cmd_code,0,sizeof(cmd_code));
		 	sprintf(cmd_code,"%d",gCfgItems.leveling_xy_speed);
		 break;
		 case z_high_level:
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.leveling_z_speed);
       	 break; 
		case Points_count:
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.leveling_point_number);
        break;	
		case Position_x:	 
			memset(cmd_code,0,sizeof(cmd_code));
		 	sprintf(cmd_code,"%d",gCfgItems.Pause_XPOS);
		 break;
		 case Position_y:
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.Pause_YPOS);
       	 break; 
		case Position_z:
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.Pause_ZADD);
        break;	
		case more_func_cnt:
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%d",gCfgItems.morefunc_cnt);	
		break;
		case more_btn_cnt:
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%d",gCfgItems.MoreItem_pic_cnt);
		break;
//		case wifi_port:
//			memset(cmd_code,0,sizeof(cmd_code));
//			sprintf(cmd_code,"%d",gCfgItems.cloud_port);
//		    break;
		case btn_textOffset:
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%d",gCfgItems.btn_text_offset);
		    break;		
	   case current_x:
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%d",gCfgItems.xCurrent);		  
		break;
	   case current_y:
		   memset(cmd_code,0,sizeof(cmd_code));
		   sprintf(cmd_code,"%d",gCfgItems.yCurrent);		 			  
		break;	
	   case current_z:
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%d",gCfgItems.zCurrent);		  		  
		break;	
	   case current_E0:
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%d",gCfgItems.e0Current);		  		  
		break;
	   case current_E1:
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%d",gCfgItems.e1Current);		  	  
		break;		
		 case Sensivisity_X:		   
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.xSensivisity); 

		 break; 
		 case Sensivisity_Y:	  
			 memset(cmd_code,0,sizeof(cmd_code));
			 sprintf(cmd_code,"%d",gCfgItems.ySensivisity); 
		 break; 
		 case Sensivisity_Z:   
			memset(cmd_code,0,sizeof(cmd_code));
			sprintf(cmd_code,"%d",gCfgItems.zSensivisity);	 
		 break;
		 default:
		 	break;
    }
    memset(key_value,0,sizeof(key_value));
    strcpy(key_value,cmd_code);
    cnt=strlen(key_value);
    temp=strchr(key_value,'.');
    if(temp)
    {
       point_flg = 0; 
    }
    else
    {
        point_flg = 1;
    }    
    TEXT_SetText(textKeyNumb, key_value);
}
void draw_NumberKey()
{   
    int i;

    if(disp_state_stack._disp_state[disp_state_stack._disp_index] != NUMBER_KEY_UI)
    {
        disp_state_stack._disp_index++;
        disp_state_stack._disp_state[disp_state_stack._disp_index] = NUMBER_KEY_UI;
    }
    disp_state = NUMBER_KEY_UI;
    
    GUI_SetBkColor(gCfgItems.background_color);
    GUI_SetColor(gCfgItems.title_color);
    GUI_Clear();
    
    hNumberKeyWnd = WM_CreateWindow(0, 0, LCD_WIDTH, LCD_HEIGHT, WM_CF_SHOW, cbNumberKeyWin, 0);

    //KeyValue.btnHandle = BUTTON_CreateEx(92,40,296,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
	textKeyNumb= TEXT_CreateEx(92,40,296,40,hNumberKeyWnd,WM_CF_SHOW, TEXT_CF_HCENTER,	GUI_ID_TEXT1, " ");

    NumberKey_1.btnHandle = BUTTON_CreateEx(92,90,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    NumberKey_2.btnHandle = BUTTON_CreateEx(168,90,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    NumberKey_3.btnHandle = BUTTON_CreateEx(244,90,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    KeyBack.btnHandle = BUTTON_CreateEx(320,90,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    NumberKey_4.btnHandle = BUTTON_CreateEx(92,140,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    NumberKey_5.btnHandle = BUTTON_CreateEx(168,140,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    NumberKey_6.btnHandle = BUTTON_CreateEx(244,140,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    KeyReset.btnHandle = BUTTON_CreateEx(320,140,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    
    NumberKey_7.btnHandle = BUTTON_CreateEx(92,190,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    NumberKey_8.btnHandle = BUTTON_CreateEx(168,190,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    NumberKey_9.btnHandle = BUTTON_CreateEx(244,190,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    KeyConfirm.btnHandle = BUTTON_CreateEx(320,190,68,90,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

    NumberKey_0.btnHandle = BUTTON_CreateEx(92,240,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());
    KeyPoint.btnHandle = BUTTON_CreateEx(244,240,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

    Nagetive.btnHandle = BUTTON_CreateEx(168,240,68,40,hNumberKeyWnd, BUTTON_CF_SHOW, 0, alloc_win_id());

	
    //sean 19.12.27
    #if 0
    BUTTON_SetBmpFileName(NumberKey_1.btnHandle, "bmp_NumberKey_bk.bin",1);        
    BUTTON_SetBmpFileName(NumberKey_2.btnHandle, "bmp_NumberKey_bk.bin",1);
    BUTTON_SetBmpFileName(NumberKey_3.btnHandle, "bmp_NumberKey_bk.bin",1);
    
    BUTTON_SetBmpFileName(NumberKey_4.btnHandle, "bmp_NumberKey_bk.bin",1);        
    BUTTON_SetBmpFileName(NumberKey_5.btnHandle, "bmp_NumberKey_bk.bin",1);
    BUTTON_SetBmpFileName(NumberKey_6.btnHandle, "bmp_NumberKey_bk.bin",1);  

    BUTTON_SetBmpFileName(NumberKey_7.btnHandle, "bmp_NumberKey_bk.bin",1);        
    BUTTON_SetBmpFileName(NumberKey_8.btnHandle, "bmp_NumberKey_bk.bin",1);
    BUTTON_SetBmpFileName(NumberKey_9.btnHandle, "bmp_NumberKey_bk.bin",1);  

    BUTTON_SetBmpFileName(NumberKey_0.btnHandle, "bmp_NumberKey_0_bk.bin",1);        
    BUTTON_SetBmpFileName(KeyPoint.btnHandle, "bmp_NumberKey_bk.bin",1);
    BUTTON_SetBmpFileName(KeyConfirm.btnHandle, "bmp_KeyConfirm.bin",1);  

    BUTTON_SetBmpFileName(KeyReset.btnHandle, "bmp_NumberKey_bk.bin",1);
    BUTTON_SetBmpFileName(KeyBack.btnHandle, "bmp_NumberKey_bk.bin",1);
    
    //BUTTON_SetBmpFileName(KeyValue.btnHandle,NULL,1);
    
    BUTTON_SetBitmapEx(NumberKey_1.btnHandle,0,&bmp_struct68X40,0,0);//图片大小为68x40
    BUTTON_SetBitmapEx(NumberKey_2.btnHandle,0,&bmp_struct68X40,0,0);
    BUTTON_SetBitmapEx(NumberKey_3.btnHandle,0,&bmp_struct68X40,0,0);
    BUTTON_SetBitmapEx(NumberKey_4.btnHandle,0,&bmp_struct68X40,0,0);//图片大小为68x40
    BUTTON_SetBitmapEx(NumberKey_5.btnHandle,0,&bmp_struct68X40,0,0);
    BUTTON_SetBitmapEx(NumberKey_6.btnHandle,0,&bmp_struct68X40,0,0);
    BUTTON_SetBitmapEx(NumberKey_7.btnHandle,0,&bmp_struct68X40,0,0);//图片大小为68x40
    BUTTON_SetBitmapEx(NumberKey_8.btnHandle,0,&bmp_struct68X40,0,0);
    BUTTON_SetBitmapEx(NumberKey_9.btnHandle,0,&bmp_struct68X40,0,0);
    BUTTON_SetBitmapEx(NumberKey_0.btnHandle,0,&bmp_struct144X40,0,0);//图片大小为68x40
    BUTTON_SetBitmapEx(KeyPoint.btnHandle,0,&bmp_struct68X40,0,0);
    BUTTON_SetBitmapEx(KeyBack.btnHandle,0,&bmp_struct68X40,0,0);
    BUTTON_SetBitmapEx(KeyReset.btnHandle,0,&bmp_struct68X40,0,0);
    BUTTON_SetBitmapEx(KeyConfirm.btnHandle,0,&bmp_struct68X90,0,0);
    #else
    BUTTON_SetBmpFileName(NumberKey_1.btnHandle, NULL,1);        
    BUTTON_SetBmpFileName(NumberKey_2.btnHandle, NULL,1);
    BUTTON_SetBmpFileName(NumberKey_3.btnHandle, NULL,1);
    
    BUTTON_SetBmpFileName(NumberKey_4.btnHandle, NULL,1);        
    BUTTON_SetBmpFileName(NumberKey_5.btnHandle, NULL,1);
    BUTTON_SetBmpFileName(NumberKey_6.btnHandle, NULL,1);  

    BUTTON_SetBmpFileName(NumberKey_7.btnHandle, NULL,1);        
    BUTTON_SetBmpFileName(NumberKey_8.btnHandle, NULL,1);
    BUTTON_SetBmpFileName(NumberKey_9.btnHandle, NULL,1);  

    BUTTON_SetBmpFileName(NumberKey_0.btnHandle, NULL,1);  
	BUTTON_SetBmpFileName(Nagetive.btnHandle, NULL,1);
	
    BUTTON_SetBmpFileName(KeyPoint.btnHandle, NULL,1);
    BUTTON_SetBmpFileName(KeyConfirm.btnHandle, NULL,1);  

    BUTTON_SetBmpFileName(KeyReset.btnHandle, NULL,1);
    BUTTON_SetBmpFileName(KeyBack.btnHandle, NULL,1);
    #endif
    
    BUTTON_SetTextAlign(NumberKey_1.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(NumberKey_2.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(NumberKey_3.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(NumberKey_4.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(NumberKey_5.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(NumberKey_6.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(NumberKey_7.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(NumberKey_8.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(NumberKey_9.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(NumberKey_0.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(KeyPoint.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(KeyBack.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );    
    BUTTON_SetTextAlign(KeyReset.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
    BUTTON_SetTextAlign(KeyConfirm.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER ); 
	BUTTON_SetTextAlign(Nagetive.btnHandle,GUI_TA_HCENTER|GUI_TA_VCENTER );
	
    
    //BUTTON_SetTextAlign(KeyValue.btnHandle,GUI_TA_LEFT|GUI_TA_VCENTER ); 
    TEXT_SetBkColor(textKeyNumb,GUI_WHITE);
    TEXT_SetTextColor(textKeyNumb,GUI_BLACK);
    TEXT_SetTextAlign(textKeyNumb,GUI_TA_VCENTER | GUI_TA_HCENTER);

    BUTTON_SetBkColor(NumberKey_1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_1.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_1.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(NumberKey_2.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_2.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_2.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_2.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(NumberKey_3.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_3.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_3.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_3.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(NumberKey_4.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_4.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_4.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_4.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(NumberKey_5.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_5.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_5.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_5.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(NumberKey_6.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_6.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_7.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_7.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(NumberKey_7.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_7.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_7.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_7.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(NumberKey_8.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_8.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_8.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_8.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(NumberKey_9.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_9.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_9.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_9.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(NumberKey_0.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(NumberKey_0.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(NumberKey_0.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(NumberKey_0.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

	BUTTON_SetBkColor(Nagetive.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(Nagetive.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(Nagetive.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(Nagetive.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(KeyPoint.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(KeyPoint.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(KeyPoint.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(KeyPoint.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(KeyBack.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(KeyBack.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(KeyBack.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(KeyBack.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(KeyReset.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(KeyReset.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(KeyReset.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(KeyReset.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    BUTTON_SetBkColor(KeyConfirm.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_color);
    BUTTON_SetBkColor(KeyConfirm.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_color); 
    BUTTON_SetTextColor(KeyConfirm.btnHandle, BUTTON_CI_PRESSED, gCfgItems.back_btn_textcolor);
    BUTTON_SetTextColor(KeyConfirm.btnHandle, BUTTON_CI_UNPRESSED, gCfgItems.back_btn_textcolor); 

    if(gCfgItems.multiple_language != 0)
    {
        BUTTON_SetText(NumberKey_1.btnHandle, machine_menu.key_1);
        BUTTON_SetText(NumberKey_2.btnHandle, machine_menu.key_2);
        BUTTON_SetText(NumberKey_3.btnHandle, machine_menu.key_3); 
        BUTTON_SetText(NumberKey_4.btnHandle, machine_menu.key_4);
        BUTTON_SetText(NumberKey_5.btnHandle, machine_menu.key_5);
        BUTTON_SetText(NumberKey_6.btnHandle, machine_menu.key_6); 
        BUTTON_SetText(NumberKey_7.btnHandle, machine_menu.key_7);
        BUTTON_SetText(NumberKey_8.btnHandle, machine_menu.key_8);
        BUTTON_SetText(NumberKey_9.btnHandle, machine_menu.key_9); 
        BUTTON_SetText(NumberKey_0.btnHandle, machine_menu.key_0);
	 	BUTTON_SetText(Nagetive.btnHandle, machine_menu.negative);
        BUTTON_SetText(KeyPoint.btnHandle, machine_menu.key_point);
        BUTTON_SetText(KeyBack.btnHandle, machine_menu.key_back);   
        BUTTON_SetText(KeyReset.btnHandle, machine_menu.key_rest);
        BUTTON_SetText(KeyConfirm.btnHandle, machine_menu.key_confirm);           
    }
    disp_value();
}

void Clear_NumberKey()
{
	GUI_SetBkColor(gCfgItems.background_color);
	if(WM_IsWindow(hNumberKeyWnd))
	{
		WM_DeleteWindow(hNumberKeyWnd);
	}
}






