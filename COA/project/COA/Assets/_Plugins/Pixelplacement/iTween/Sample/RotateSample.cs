using UnityEngine;
using System.Collections;

public class RotateSample : MonoBehaviour
{	
	void Start(){
		iTween.RotateBy(gameObject, iTween.Hash("x", 0.25, "easeType", "easeInOutBack", "loopType", "pingPong", "delay", 0.1));
		//gameObject.mo
		//iTween.DrawLine()
	}
}

