#ifndef _AFROAD_
#define _AFROAD_
#include <stdint.h>


#define const_max_bound_num  (2)
#define const_max_line_num  (8)
#define const_max_lane_num  (8)
#define	const_max_road_num	(9)

/// errorCode
#define LDIC_A0_ULTRALIMIT_MASK				0x00000001
#define LDIC_A1_ULTRALIMIT_MASK	 			0x00000002
#define LDIC_A2_ULTRALIMIT_MASK	 			0x00000004
#define LDIC_A3_ULTRALIMIT_MASK				0x00000008
#define LDIC_LANEID_ULTRALIMIT_MASK			0x00000010 
#define LDIC_LANETYPE_ULTRALIMIT_MASK		0x00000020
#define LDIC_LANECOLOR_ULTRALIMIT_MASK		0x00000040
#define LDIC_LANEQUALITY_ULTRALIMIT_MASK	0x00000080
#define LDIC_LANEWIDTH_ULTRALIMIT_MASK		0x00000100
#define LDIC_VALIDSTADIS_ULTRALIMIT_MASK	0x00000200
#define LDIC_VALIDENDDIS_ULTRALIMIT_MASK	0x00000400
#define LDIC_LANEPOS_ULTRALIMIT_MASK		0x00000800

typedef enum {
	LINETYPE_NULL = 0,
	LINETYPE_DASHED = 1,
	LINETYPE_SOLID = 2,
	LINETYPE_DOUBLE_SOLID = 3,
	LINETYPE_INNER_DASH_OUTER_SOLID = 4,
	LINETYPE_INNER_SOLID_OUTER_DASH = 5,
	LINETYPE_DOUBLE_DASH = 6,
	LINETYPE_CONE_BARREL,
	LINETYPE_GUARDRAIL,
	LINETYPE_SINK,
	LINETYPE_CURB,
	LINETYPE_WALL,
	LINETYPE_GREENBELT,
	LINETYPE_GRASS,
	LINETYPE_WATERHORSE,
	LINETYPE_LINECURB,
	LINETYPE_RESERVE
}afLineType;

typedef enum {
	LINECOLOR_NONE = 0,
	LINECOLOR_YELLOW = 1,
	LINECOLOR_WHITE = 2,
	LINECOLOR_BLUE = 3,
	LINECOLOR_ORANGE = 4,
	LINECOLOR_RESERVE
}afLineColor;


typedef enum {
	LANETYPE_UNKNOWN,
	LANETYPE_CITY_DRIVING,
	LANETYPE_EMERGENCY
}afLaneType;


typedef enum {
	LANEDIRECTION_POSITIVE_DIRECTION = 0,
	LANEDIRECTION_NEGATIVE_DIRECTION = 1,
	LANEDIRECTION_BOTH_DIRECTIONS = 2
}afLaneDirection;


typedef enum {
	LANETURN_NO_TURN = 0,
	LANETURN_LEFT_TURN,
	LANETURN_RIGHT_TURN,
	LANETURN_U_TURN
}afLaneTurn;

typedef enum {
	LINEPOSITION_UNDEFINED,
	LINEPOSITION_LEFT_NEIGHBOR,
	LINEPOSITION_LEFT,
	LINEPOSITION_RIGHT,
	LINEPOSITION_RIGHT_NEIGHBOR
}afLinePosition;


typedef enum {
	LINEQUALITY_BAD,
	LINEQUALITY_MIDDLE,
	LINEQUALITY_GOD,
	LINEQUALITY_BEST
}afLineQuality;

typedef enum {
	UNKNOWN,
	LINECAMERA,
	LINEHDMAP,
	LINEFUSION
}afLineSource;

typedef enum {
	ROADTYPE_OTHER,
	ROADTYPE_MAIN,
	ROADTYPE_SIDE,
	ROADTYPE_RAMP
}afRoadType;

typedef struct {
	uint32_t		Id; 
	int32_t			LineStart; 
	int32_t			LineEnd; 
	int32_t		    LineWidth;
	double			LineA0;
	double			LineA1;
	double			LineA2;
	double			LineA3;
 //   uint32_t        SuccessorLineIDS[4];
 //   uint32_t        PrecursorLineIDS[4];
 //   uint32_t        ReserveUint[8];
 //   float           ReserveFloat[8];
	//float           extraPointsX[5];
	//float           extraPointsY[5];
	afLineType		LineType : 8;
	afLineColor		LineColor : 8;
	afLineQuality	LineQuality : 8;
	afLinePosition	Position : 8; 
	afLineSource    LineSource :8; 
	//uint8_t 		extraPointsType[5];
	//uint8_t			reserved[2];
}ARoadLine; 

typedef struct {
	uint16_t		LaneWidth; 
	uint16_t        LaneTTLC; 
	uint16_t		maxLaneSpeed; 
	uint16_t		minLaneSpeed; 
	float			SlopeA0; 
	float			SlopeA1; 
	float			SlopeA2; 
	float			SlopeA3; 
	int32_t			SlopeStartX; 
	int32_t			SlopeEndX; 
	uint32_t		LaneLeftLineID; 
	uint32_t		LaneRightLineID; 
	uint32_t		ID;
	afLaneType		LaneType : 8;
	afLaneDirection	LaneDirection : 8;
	afLaneTurn		LaneTurn : 8; 
	uint8_t			reserved; 
}AFusionLane; 

typedef struct {
	uint32_t	    BoudaryNum; 
	uint32_t		LineNum; 
	uint32_t		LaneNum; 
	uint32_t		ID;
    uint32_t        PathID; 
	ARoadLine		Boudaries[const_max_bound_num]; 
	ARoadLine		Lines[const_max_line_num];
	AFusionLane		Lanes[const_max_lane_num];  
	afRoadType		RoadType : 8; 
	uint8_t			reserved[3];
}ARoad;


typedef struct 
{
	uint32_t		Num;  
	uint32_t		ProtocolVersion;
	uint64_t	    Timestamp; 
	uint64_t	    FrameID;  
	ARoad		    Road[const_max_road_num]; 
}AFusionRoads; 



#endif
